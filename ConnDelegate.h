//
//  ConnDelegate.h
//  CppTest38
//
//  Created by Buwenjie on 15/10/20.
//
//

#ifndef ConnDelegate_h
#define ConnDelegate_h

#include "net/impl/ConnDelegateImpl.h"
#include "GameManager.h"
#include "UIThreadTask.h"
#include "cocos2d.h"

class ConnDelegate : public ConnDelegateImpl {
public:
    virtual void onConnect() override;
    virtual void onDisconnect() override;
    virtual void onError() override;
    virtual void onRecv(const ByteArray& bytes) override;
    
private:
    ProtoService<cocos2d::ValueMap>* _service_proto;
    ConnectService* _service_connect;
    UIThreadTask* _task_thread;
};

#endif /* ConnDelegate_h */
