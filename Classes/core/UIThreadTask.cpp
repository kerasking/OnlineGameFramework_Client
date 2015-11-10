//
//  UIThreadTask.cpp
//  CppTest38
//
//  Created by Buwenjie on 15/10/12.
//
//

#include "UIThreadTask.h"
#include <utility>

USING_NS_CC;

UIThreadTask* UIThreadTask::getInstance() {
    static UIThreadTask instance;
    return &instance;
}

UIThreadTask::UIThreadTask()
: _queue_proto(512)
, _queue_task(512) {
    
}

void UIThreadTask::push_proto(const ValueMap& data) {
    _queue_proto.enqueue(data);
}

std::vector<ValueMap> UIThreadTask::pop_protos() {
    std::vector<ValueMap> vec;
    while(!_queue_proto.empty()) {
        vec.push_back(_queue_proto.dequeue());
    }
    
    return vec; // 自动右值引用
}

void UIThreadTask::push_task(Task t) {
    _queue_task.enqueue(t);
}

std::vector<Task> UIThreadTask::pop_tasks() {
    std::vector<Task> vec;
    while(!_queue_task.empty()) {
        vec.push_back(_queue_task.dequeue());
    }
    return vec;
}
