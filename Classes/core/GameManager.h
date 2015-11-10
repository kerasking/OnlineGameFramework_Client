//
//  GameManager.h
//  CppTest38
//
//  Created by Buwenjie on 15/10/14.
//
//

#ifndef GameManager_h
#define GameManager_h

#include "net/service/ConnectService.h"
#include "net/service/ProtoService.hpp"
#include "ConnDelegate.h"

class GameManager {
public:
    void init();
    void start();
    void stop();
    
    void sendProto(const cocos2d::ValueMap& dict);
    
    ProtoService<cocos2d::ValueMap>* protoService();
    ConnectService*                  connectService();

    ConnDelegate* connDelegate();
    
    static GameManager* getInstance();
    
private:
    GameManager();
    
    ProtoService<cocos2d::ValueMap>* _service_proto;
    ConnectService* _service_connect;
    
    ConnDelegate* _delegate_conn;
};

#endif /* GameManager_h */
