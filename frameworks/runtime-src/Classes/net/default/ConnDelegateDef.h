//
//  ConnDelegateDef.h
//  OnlineGameFramework_Client
//
//  Created by Buwenjie on 15/10/19.
//
//

#ifndef ConnDelegateDef_h
#define ConnDelegateDef_h

#include "net/impl/ConnDelegateImpl.h"

namespace red {

class ConnDelegateDef : public ConnDelegateImpl {
public:
    virtual void onConnect() override;
    virtual void onDisconnect() override;
    virtual void onError() override;
    virtual void onRecv(const ByteArray& bytes) override;
};
    
}

#endif /* ConnDelegateDef_h */
