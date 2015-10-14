//
//  ConnectService.cpp
//  CppTest38
//
//  Created by Buwenjie on 15/9/29.
//
//

#include "ConnectService.h"
#include <functional>

#include "ByteArray.h"

ConnectService::ConnectService(ProtoDelegate* delegate_proto, ConnectDelegate* delegate_conn)
: _bytes(ByteEndian::BIG)
, _delegate_proto(delegate_proto)
, _delegate_conn(delegate_conn)
, _running(false) {
    
}

void ConnectService::run(const char* ip, unsigned short port) {
    _running = true;
    _socket = new Socket();
    _socket->async_connect(ip, port,
                           std::bind(&ConnectService::on_connect, this, std::placeholders::_1));
}

bool ConnectService::running() {
    return _running;
}

int ConnectService::send_proto(const std::string& proto, cocos2d::ValueMap& data) {
    auto bytes = _delegate_proto->pack(proto, data);
    return _socket->async_send(bytes.first(), bytes.size(),
                               std::bind(&ConnectService::on_send, this, std::placeholders::_1));
}

void ConnectService::on_connect(bool succ) {
    if(!succ) {
        on_disconnect();
        return;
    }
    _socket->asyncIO_start();
    recv_some();
}

void ConnectService::on_disconnect() {
    _running = false;
    _delegate_conn->on_disconnect();
    
    printf("socket disconnect...");
}

void ConnectService::on_send(ssize_t len) {
    if(len < 0) {
        on_disconnect();
    }
}

void ConnectService::on_recv(ssize_t len) {
    if(len < 0) {
        on_disconnect();
        return;
    }
    
    _bytes.writeBytes(_buffer, len);
    
    int check = _delegate_proto->check_bytes(_bytes);
    if(check >= 0) {
        _delegate_conn->on_recv_proto(_delegate_proto->unpack(_bytes));
        _bytes.erase(check);
    }
    
    // 继续下一次接收
    recv_some();
}

void ConnectService::recv_some() {
    _socket->async_recv(_buffer, BUFFER_SIZE,
                        std::bind(&ConnectService::on_recv, this, std::placeholders::_1));
}
