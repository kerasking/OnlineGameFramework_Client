//
//  UIThreadTask.cpp
//  OnlineGameFramework_Client
//
//  Created by Buwenjie on 15/10/12.
//
//

#include "UIThreadTask.h"
#include <utility>

USING_NS_CC;
using namespace red;

UIThreadTask* UIThreadTask::getInstance() {
    static UIThreadTask instance;
    return &instance;
}

UIThreadTask::UIThreadTask()
: _queue_proto(512)
, _queue_task(512) {
    
}

void UIThreadTask::push_proto(const ValueMap& data) {
    std::lock_guard<std::mutex> lock(_mutex_proto);
    _queue_proto.enqueue(data);
}

ValueVector UIThreadTask::pop_protos() {
    std::lock_guard<std::mutex> lock(_mutex_proto);
    ValueVector vec;
    while(!_queue_proto.empty()) {
        vec.push_back(Value(_queue_proto.dequeue()));
    }
    return vec; // 自动右值引用
}

void UIThreadTask::push_task(Task t) {
    std::lock_guard<std::mutex> lock(_mutex_task);
    _queue_task.enqueue(t);
}

void UIThreadTask::do_tasks() {
    std::lock_guard<std::mutex> lock(_mutex_task);
    while(!_queue_task.empty()) {
        auto task = _queue_task.dequeue();
        task();
    }
}

//std::vector<Task> UIThreadTask::pop_tasks() {
//    std::vector<Task> vec;
//    while(!_queue_task.empty()) {
//        vec.push_back(_queue_task.dequeue());
//    }
//    return vec;
//}
