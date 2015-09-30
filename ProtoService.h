//
//  ProtoService.hpp
//  CppTest38
//
//  Created by Buwenjie on 15/9/29.
//
//

#ifndef ProtoService_h
#define ProtoService_h

#include <string>
#include "cocos2d.h"
#include "Socket.h"
#include "ByteArray.h"

#define BUFFER_SIZE 4096

class ProtoService {
public:
    static ProtoService* getInstance();
    
    int sendProto(const std::string& proto, cocos2d::ValueMap& data);
    void onRecvProto();
    
    void checkBytes(); // 检查接收的字节是否足够
    
    void onConnect(bool succ);
    void onSend(ssize_t len);
    void onRecv(ssize_t len);
    
    
private:
    ProtoService();
    
    Socket* _socket;
    
    byte _buffer[BUFFER_SIZE];
    ByteArray _bytes;
};

#endif /* ProtoService_h */
