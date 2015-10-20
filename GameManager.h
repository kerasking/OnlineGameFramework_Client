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

class GameManager {
public:
    void start();
    void stop();
    
    ProtoService<cocos2d::ValueMap>* protoService();
    ConnectService*                  connectService();
    
    static GameManager* getInstance();
    
private:
    GameManager();
    
    ProtoService<cocos2d::ValueMap>* _service_proto;
    ConnectService* _service_connect;
    
};

#endif /* GameManager_h */
