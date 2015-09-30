//
//  ProtoService.cpp
//  CppTest38
//
//  Created by Buwenjie on 15/9/29.
//
//

#include "ProtoService.h"
#include "ByteArray.h"
#include <functional>

USING_NS_CC;

ProtoService::ProtoService() {
    _socket = new Socket();
    _socket->async_connect("127.0.0.1", 7464, <#std::function<void (bool)> callback#>)
}

ProtoService* ProtoService::getInstance() {
    static ProtoService instance;
    return &instance;
}

int ProtoService::sendProto(const std::string& proto, ValueMap& data) {
    ByteArray b(ByteEndian::BIG);
    
    // todo 分析proto文件的字段，从data中取出相应字段的数据，打包到buffer
    b.writeInt32(data["id"].asInt());
    b.writeString(data["name"].asString());
    
    return _socket->async_send(b.first(), b.size(),
                        std::bind(&ProtoService::onSend, this, std::placeholders::_1));
}

void ProtoService::onRecvProto() {
    size_t len = _bytes.readInt16(0);
    uint8_t mod = _bytes.readInt8(2);
    uint8_t act = _bytes.readInt8(3);
    
    
}

void ProtoService::checkBytes() {
    if(_bytes.size() < 4) {
        return;
    }
    // todo 各种判断协议接收完整性
    
    // todo 如果完整
    onRecvProto();
}

void ProtoService::onConnect(bool succ) {
    if(!succ) {
        log("connect fail...");
        return;
    }
    _socket->asyncIO_start();
    _socket->async_recv(_buffer, BUFFER_SIZE,
                        std::bind(&ProtoService::onRecv, this, std::placeholders::_1));
}

void ProtoService::onSend(ssize_t len) {
    if(len < 0) {
        // todo 发送失败处理
        return;
    }
}

void ProtoService::onRecv(ssize_t len) {
    if(len < 0) {
        // todo 接收失败处理
        return;
    }
    checkBytes();
    _bytes.writeBytes(_buffer, len);
}

