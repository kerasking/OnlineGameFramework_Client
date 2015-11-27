//
//  Socket.cpp
//  OnlineGameFramework_Client
//
//  Created by Buwenjie on 15/9/21.
//
//

#include "Socket.h"
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <thread>

SendBuffer::SendBuffer() {
}

SendBuffer::SendBuffer(const byte* buffer, size_t size, socket_callback callback)
: _callback(callback) {
    _data.reserve(size);
    _data.insert(_data.begin(), buffer, buffer + size);
}


RecvBuffer::RecvBuffer() {
}

RecvBuffer::RecvBuffer(byte* buffer, size_t size, socket_callback callback)
: _buffer(buffer)
, _size(size)
, _callback(callback) {
    
}


Socket::Socket()
: _running(false)
, _thread_send(nullptr)
, _thread_recv(nullptr)
, _sockfd(-1) {
    
}


Socket::Socket(int sockfd) : Socket() {
    _sockfd = sockfd;
    _running = true;
}


Socket::~Socket() {
    stop();
}


void Socket::stop() {
    _running = false;
    
    _condition_send.notify_all();
    if(_thread_send) {
        _thread_send->join();
        delete _thread_send;
        _thread_send = nullptr;
    }
    
    _condition_recv.notify_all();
    if(_thread_recv) {
        _thread_recv->join();
        delete _thread_recv;
        _thread_recv = nullptr;
    }
    
    if(_sockfd >= 0) {
        close(_sockfd);
        _sockfd = -1;
    }
}


bool Socket::bind(uint16_t port) {
    _addr_local.sin_family = AF_INET;
    _addr_local.sin_addr.s_addr = INADDR_ANY;
    _addr_local.sin_port = htons(port);
    return ::bind(_sockfd, (struct sockaddr*)&_addr_local, sizeof(struct sockaddr)) == 0;
}


bool Socket::listen(uint16_t port, int size) {
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(_sockfd < 0) {
        return false;
    }
    
    this->bind(port);
    _running = (::listen(_sockfd, size) == 0);
    return _running;
}


Socket* Socket::accept() {
    struct sockaddr_in addr_remote;
    socklen_t length = sizeof(addr_remote);
    
    int remote = ::accept(_sockfd, (struct sockaddr*)&addr_remote, &length);
    if(remote < 0) {
        return nullptr;
    }
    return new Socket(remote);
}


bool Socket::connect(const char* ip, uint16_t port) {
    this->bind(0);
    
    struct sockaddr_in addr_remote;
    addr_remote.sin_addr.s_addr = inet_addr(ip);
    addr_remote.sin_family = AF_INET;
    addr_remote.sin_port = htons(port);
    
    int sockfd_remote = socket(addr_remote.sin_family, SOCK_STREAM, 0);
    if(::connect(sockfd_remote, (sockaddr*)&addr_remote, sizeof(addr_remote)) < 0) {
        close(sockfd_remote);
        return false;
    }
    _sockfd = sockfd_remote;
    _running = true;
    return true;
}


ssize_t Socket::send(const byte* buffer, size_t size) {
    auto len = ::send(_sockfd, buffer, size, 0);
    if(len <= 0) {
        _running = false;
    }
    return len;
}


ssize_t Socket::recv(byte* buffer, size_t size) {
    auto len = ::recv(_sockfd, buffer, size, 0);
    if(len <= 0) {
        _running = false;
    }
    return len;
}


int Socket::asyncIO_start(ASYNC_TYPE type,  int queue_send_size, int queue_recv_size) {
    printf("asyncIO start...\n");
    
    _queue_send = new Circularqueue<SendBuffer*>(queue_send_size);
    _queue_recv = new Circularqueue<RecvBuffer*>(queue_recv_size);
    
    switch(type) {
        case ASYNC_TYPE::KEEP:
            run_thread_send_keep();
            run_thread_recv_keep();
            break;
            
        case ASYNC_TYPE::AUTO_WAIT:
            run_thread_send_autowait();
            run_thread_recv_autowait();
            break;
            
        default:
            printf("unknown ASYNC_TYPE\n");
            break;
    }
    return 0;
}


int Socket::async_send(const byte *buffer, size_t size, socket_callback callback) {
    auto buf = new SendBuffer(buffer, size, callback);
    
    int result = 0;
    {
        std::lock_guard<std::mutex> lock(_mutex_queue_send);
        result = _queue_send->enqueue(buf) ? 0 : -1;
    }
    
    if(result == 0) {
        // buf在发送之后释放
        _condition_send.notify_all();
    } else {
        delete buf;
    }
    
    return result;
}


int Socket::async_recv(byte *buffer, size_t size, socket_callback callback) {
    auto buf = new RecvBuffer(buffer, size, callback);
    
    int result = 0;
    {
        std::lock_guard<std::mutex> lock(_mutex_queue_recv);
        result = _queue_recv->enqueue(buf) ? 0 : -1;
    }
    
    if(result == 0) {
        // buf在接收之后释放
        _condition_recv.notify_all();
    } else {
        delete buf;
    }
    
    return result;
}


void Socket::async_connect(const char *ip, uint16_t port, const std::function<void(bool)> callback) {
    std::thread thread_conn([=]() {
        callback(connect(ip, port));
    });
    thread_conn.detach();
}

void Socket::run_thread_send_keep() {
    assert(_thread_send == nullptr);
    _thread_send = new std::thread([=]() {
        printf("++++ send thread start...\n");
        while(running()) {
            if(!_queue_send->empty()) {
                printf("++++ send thread work...\n");
                
                SendBuffer* buf;
                {
                    std::lock_guard<std::mutex> lock(_mutex_queue_send);
                    buf = _queue_send->dequeue();
                }
                
                buf->_callback(this->send(buf->_data.data(), buf->_data.size()));
                delete buf;
            }
        }
        printf("++++ send thread stop...\n");
    });
}

void Socket::run_thread_recv_keep() {
    assert(_thread_recv == nullptr);
    _thread_recv = new std::thread([=]() {
        printf("---- recv thread start...\n");
        while(running()) {
            if(!_queue_recv->empty()) {
                printf("---- recv thread work...\n");
                
                RecvBuffer* buf;
                {
                    std::lock_guard<std::mutex> lock(_mutex_queue_send);
                    buf = _queue_recv->dequeue();
                }
                
                buf->_callback(this->recv(buf->_buffer, buf->_size));
                delete buf;
            }
        }
        printf("---- recv thread stop...\n");
    });
}

void Socket::run_thread_send_autowait() {
    assert(_thread_send == nullptr);
    _thread_send = new std::thread([=](){
        printf("++++ send thread start...\n");
        while(running()) {
            while(_queue_send->empty() && running()) {
                printf("++++ send thread wait...\n");
                
                std::unique_lock<std::mutex> lock(_mutex_cond_send);
                _condition_send.wait(lock);
            }
            
            if(running()) {
                printf("++++ send thread work...\n");
                
                SendBuffer* buf;
                {
                    std::lock_guard<std::mutex> lock(_mutex_queue_send);
                    buf = _queue_send->dequeue();
                }
                
                buf->_callback(this->send(buf->_data.data(), buf->_data.size()));
                delete buf;
            }
        }
        printf("++++ send thread stop...\n");
    });
}

void Socket::run_thread_recv_autowait() {
    assert(_thread_recv == nullptr);
    _thread_recv = new std::thread([=](){
        printf("---- recv thread start...\n");
        while(running()) {
            while(_queue_recv->empty() && running()) {
                printf("---- recv thread wait...\n");
                
                std::unique_lock<std::mutex> lock(_mutex_cond_recv);
                _condition_recv.wait(lock);
            }
            
            if(running()) {
                printf("---- recv thread work...\n");
                
                RecvBuffer* buf;
                {
                    std::lock_guard<std::mutex> lock(_mutex_queue_recv);
                    buf = _queue_recv->dequeue();
                }
                
                buf->_callback(this->recv(buf->_buffer, buf->_size));
                delete buf;
            }
        }
        printf("---- recv thread stop...\n");
    });
}
