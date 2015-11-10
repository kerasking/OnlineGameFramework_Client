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
#include "UIThreadTask.h"

class ConnDelegate : public ConnDelegateImpl {
public:
    ConnDelegate();
    
    virtual void onConnect() override;
    virtual void onDisconnect() override;
    virtual void onError() override;
    virtual void onRecv(const ByteArray& bytes) override;
    
    void bindConnect(Task t);
    void bindDisconnect(Task t);
    void bindError(Task t);
    
private:
    UIThreadTask* _task_thread;
    
    Task _task_conn;
    Task _task_disconn;
    Task _task_err;
};

#endif /* ConnDelegate_h */
