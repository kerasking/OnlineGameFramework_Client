//
//  ConnDelegateImpl.h
//  OnlineGameFramework_Client
//
//  Created by Buwenjie on 15/10/12.
//
//

#ifndef ConnDelegateImpl_h
#define ConnDelegateImpl_h

#include "net/tools/ByteArray.h"

class ConnDelegateImpl {
public:
    virtual ~ConnDelegateImpl() {}
    
    virtual void onConnect() = 0;
    virtual void onDisconnect() = 0;
    virtual void onError() = 0;
    virtual void onRecv(const ByteArray& bytes) = 0;
};

#endif /* ConnDelegateImpl_h */
