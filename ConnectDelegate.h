//
//  ConnectDelegate.h
//  CppTest38
//
//  Created by Buwenjie on 15/10/12.
//
//

#ifndef ConnectDelegate_h
#define ConnectDelegate_h

#include "cocos2d.h"

class ConnectDelegate {
public:
    void on_disconnect();
    void on_recv_proto(const cocos2d::ValueMap& data);
};

#endif /* ConnectDelegate_h */
