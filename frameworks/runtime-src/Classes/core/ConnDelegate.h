//
//  ConnDelegate.h
//  OnlineGameFramework_Client
//
//  Created by Buwenjie on 15/10/20.
//
//

#ifndef ConnDelegate_h
#define ConnDelegate_h

#include "net/impl/ConnDelegateImpl.h"
#include "UIThreadTask.h"

namespace red {

class ConnDelegate : public ConnDelegateImpl {
public:
    virtual void onConnect() override;
    virtual void onDisconnect() override;
    virtual void onError() override;
    virtual void onRecv(const ByteArray& bytes) override;
    
private:
    
};
    
}

#endif /* ConnDelegate_h */
