//
//  UIThreadTask.h
//  CppTest38
//
//  Created by Buwenjie on 15/10/12.
//
//  需要主线程调用的任务。其中协议处理也在主线程中。
//  任务和协议每一帧都不得超过512个，因为队列长度为512，超过肯定是设计问题

#ifndef UIThreadTask_h
#define UIThreadTask_h

#include "cocos2d.h"
#include "Circularqueue.hpp"
#include <functional>

typedef std::function<void()> Task;

class UIThreadTask {
public:
    void push_proto(const cocos2d::ValueMap& data);
    std::vector<cocos2d::ValueMap> pop_protos();
    
    void push_task(Task t);
    std::vector<Task> pop_tasks();
    
    static UIThreadTask* getInstance();
    
private:
    UIThreadTask();
    
    Circularqueue<cocos2d::ValueMap> _queue_proto;
    Circularqueue<Task> _queue_task;
};

#endif /* UIThreadTask_h */
