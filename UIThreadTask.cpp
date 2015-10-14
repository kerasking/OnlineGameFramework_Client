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
: _queue_proto(256) {
    
}

void UIThreadTask::push_proto(const ValueMap& data) {
    _queue_proto.enqueue(data);
}

ValueVector UIThreadTask::pop_protos() {
    ValueVector vector;
    while(!_queue_proto.empty()) {
        vector.push_back(Value(_queue_proto.dequeue()));
    }
    
    return std::move(vector);
}

