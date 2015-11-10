//
//  ConnectService.h
//  CppTest38
//
//  Created by Buwenjie on 15/9/29.
//
//

#ifndef ConnectService_h
#define ConnectService_h

#include <string>
#include "cocos2d.h"

#include "Socket.h"
#include "ByteArray.h"
#include "net/impl/ConnDelegateImpl.h"

const size_t BUFFER_SIZE = 1024 * 8;

class ConnectService {
public:
    ConnectService(ConnDelegateImpl* delegate);
    ~ConnectService();
    
    void run(const char* ip, unsigned short port);
    void stop();
    
    int  sendProto(const ByteArray& proto);
    
private:
    void onConnect(bool succ);
    void onDisconnect();
    void onSend(ssize_t len);
    void onRecv(ssize_t len);
    
    void recvSome();
    int  checkBytes(const ByteArray& bytes); // 检查长度，返回消息体（不包括分包需要的前两个字节）的长度
    
    Socket*              _socket;
    ConnDelegateImpl* _delegate;
    
    byte      _buffer[BUFFER_SIZE];
    ByteArray _bytes;
};

#endif /* ConnectService_h */
