//
//  ConnectService.cpp
//  CppTest38
//
//  Created by Buwenjie on 15/9/29.
//
//

#include "ConnectService.h"
#include <functional>

ConnectService::ConnectService(ConnDelegateImpl* delegate)
: _bytes(ByteEndian::BIG)
, _delegate(delegate) {
    
}

ConnectService::~ConnectService() {
    delete _delegate;
}

void ConnectService::run(const char* ip, unsigned short port) {
    _socket = new Socket();
    _socket->async_connect(ip, port,
                           std::bind(&ConnectService::onConnect, this, std::placeholders::_1));
}

void ConnectService::stop() {
    if(_socket) {
        delete _socket;
        _socket = nullptr;
    }
    _delegate->onDisconnect();
}

int ConnectService::sendProto(const ByteArray& proto) {
    ByteArray bytes(proto.endian());
    bytes.writeInt16(proto.size());
    bytes.writeBytes(proto.first(), proto.size());
    return _socket->async_send(bytes.first(), bytes.size(),
                               std::bind(&ConnectService::onSend, this, std::placeholders::_1));
}

void ConnectService::onConnect(bool succ) {
    _socket->asyncIO_start();
    _delegate->onConnect();
    recvSome();
}

void ConnectService::onDisconnect() {
    _delegate->onDisconnect();
}

void ConnectService::onSend(ssize_t len) {
    if(len < 0) {
        _delegate->onError();
    }
}

void ConnectService::onRecv(ssize_t len) {
    if(len < 0) {
        _delegate->onError();
    }
    _bytes.writeBytes(_buffer, len);
    int size = checkBytes(_bytes);
    if(size >= 0) {
        ByteArray protoBytes(_bytes.endian());
        protoBytes.writeBytes(_bytes.first()+2, size);
        _delegate->onRecv(protoBytes);
        
        // 擦除缓冲区的字节
        _bytes.erase(size);
    }
    // 继续接收
    recvSome();
}

void ConnectService::recvSome() {
    _socket->async_recv(_buffer, BUFFER_SIZE,
                        std::bind(&ConnectService::onRecv, this, std::placeholders::_1));
}

int ConnectService::checkBytes(const ByteArray& bytes) {
    if(bytes.size() < 2) {
        return -1;
    }
    
    auto len = bytes.readInt16(0);
    if(bytes.size() < len + 2) {
        return -1;
    }
    
    return len;
}
