//
//  GameManager.h
//  OnlineGameFramework_Client
//
//  Created by Buwenjie on 15/10/14.
//
//

#ifndef GameManager_h
#define GameManager_h

#include "net/service/ConnectService.h"
#include "net/service/ProtoService.hpp"
#include "net/default/Encoder.h"
#include "net/default/Decoder.h"
#include "ConnDelegate.h"

// 为了绑定到lua，不能使用模板类，因此此处写一个子类
class ProtoServiceEntity : public ProtoService<cocos2d::ValueMap> {
public:
    ProtoServiceEntity(Encoder* encoder, Decoder* decoder);
};

class GameManager {
public:
    void init();
    void start();
    void stop();
    
    void sendProto(const cocos2d::ValueMap& dict);
    
    ProtoServiceEntity* protoService();
    ConnectService*     connectService();

    ConnDelegate* connDelegate();
    
    static GameManager* getInstance();
    
private:
    GameManager();
    
    ProtoServiceEntity* _service_proto;
    ConnectService* _service_connect;
    
    ConnDelegate* _delegate_conn;
};

#endif /* GameManager_h */
