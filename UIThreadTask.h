//
//  UIThreadTask.h
//  CppTest38
//
//  Created by Buwenjie on 15/10/12.
//
//

#ifndef UIThreadTask_h
#define UIThreadTask_h

#include "cocos2d.h"
#include "Circularqueue.hpp"

class UIThreadTask {
public:
    cocos2d::ValueVector pop_protos();
    void                 push_proto(const cocos2d::ValueMap& data);
    
    static UIThreadTask* getInstance();
    
private:
    UIThreadTask();
    
    Circularqueue<cocos2d::ValueMap> _queue_proto;
};

#endif /* UIThreadTask_h */
