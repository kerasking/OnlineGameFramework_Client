//
//  UIThreadTask.h
//  OnlineGameFramework_Client
//
//  Created by Buwenjie on 15/10/12.
//
//  需要主线程调用的任务。其中协议处理也在主线程中。
//  任务和协议每一帧都不得超过512个，因为队列长度为512，超过肯定是设计问题

#ifndef UIThreadTask_h
#define UIThreadTask_h

#include "cocos2d.h"
#include "net/tools/Circularqueue.hpp"
#include <functional>
#include <mutex>

namespace red {
    
typedef std::function<void()> Task;

class UIThreadTask {
public:
    void push_proto(const cocos2d::ValueMap& data);
    cocos2d::ValueVector pop_protos();
    
    void push_task(Task t);
    void do_tasks();
    
    // 绑定到lua用vector出错，所以改成c++执行
    //std::vector<Task> pop_tasks();
    
    static UIThreadTask* getInstance();
    
private:
    UIThreadTask();
    
    Circularqueue<cocos2d::ValueMap> _queue_proto;
    Circularqueue<Task> _queue_task;
    
    std::mutex _mutex_proto;
    std::mutex _mutex_task;
};
    
}

#endif /* UIThreadTask_h */
