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
#include "ProtoDelegate.h"
#include "ConnectDelegate.h"

const size_t BUFFER_SIZE = 1024 * 8;

class ConnectService {
public:
    ConnectService(ProtoDelegate* delegate, ConnectDelegate* delegate_conn);
    
    void run(const char* ip, unsigned short port);
    inline bool running();
    
    int send_proto(const std::string& proto, cocos2d::ValueMap& data);
    
private:
    void on_connect(bool succ);
    void on_disconnect();
    void on_send(ssize_t len);
    void on_recv(ssize_t len);
    
    void recv_some();
    
    Socket* _socket;
    ProtoDelegate*   _delegate_proto;
    ConnectDelegate* _delegate_conn;
    
    byte _buffer[BUFFER_SIZE];
    ByteArray _bytes;
    
    bool _running;
};

#endif /* ConnectService_h */
