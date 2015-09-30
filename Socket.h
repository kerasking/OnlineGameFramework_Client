//
//  Socket.h
//
//  Created by Buwenjie on 15/9/21.
//
//

#ifndef __cpp_test__Socket__
#define __cpp_test__Socket__

#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <functional>
#include "Circularqueue.hpp"
#include <mutex>
#include <thread>
#include <condition_variable>

// 发送和接收线程的异步类型
enum class ASYNC_TYPE {
    KEEP,       // 发送和接收线程保持运行，不会挂起
    AUTO_WAIT   // 发送和接收线程在队列为空时，自动挂起
};

typedef uint8_t byte;
typedef std::function<void (ssize_t)> socket_callback;

class SendBuffer {
public:
    SendBuffer();
    SendBuffer(byte* buffer, size_t size, socket_callback callback);
    
public:
    std::vector<byte>   _data;
    socket_callback     _callback;
};


class RecvBuffer {
public:
    RecvBuffer();
    RecvBuffer(byte* buffer, size_t size, socket_callback callback);
    
public:
    byte*           _buffer;
    size_t          _size;
    socket_callback _callback;
};


class Socket {
public:
    Socket();
    Socket(int sockfd);
    
    ~Socket();
    
    inline bool running();
    
    bool    connect(const char* ip, ushort port);
    bool    listen(ushort port, int size);
    Socket* accept();
    
    ssize_t send(byte* buffer, size_t size);
    ssize_t recv(byte* buffer, size_t size);
    
    int asyncIO_start(ASYNC_TYPE type = ASYNC_TYPE::AUTO_WAIT,
                    int queue_send_size = 1024,
                    int queue_recv_size = 1024);
    
    int async_send(byte* buffer, size_t size, socket_callback callback);
    int async_recv(byte* buffer, size_t size, socket_callback callback);
    
    void async_connect(const char* ip, ushort port, std::function<void(bool)> callback);
    
private:
    bool bind(ushort port);
    
    bool                _running;
    int                 _sockfd;
    struct sockaddr_in  _addr_local;
    
    Circularqueue <SendBuffer*>*  _queue_send;
    Circularqueue <RecvBuffer*>*  _queue_recv;
    
    std::mutex _mutex_queue_send;
    std::mutex _mutex_queue_recv;
    
    std::thread* _thread_send;
    std::thread* _thread_recv;
    
    std::condition_variable _condition_send;
    std::condition_variable _condition_recv;
    
    std::mutex _mutex_cond_send;
    std::mutex _mutex_cond_recv;
};

#endif /* defined(__cpp_test__Socket__) */
