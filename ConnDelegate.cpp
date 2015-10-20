//
//  ConnDelegate.cpp
//  CppTest38
//
//  Created by Buwenjie on 15/10/20.
//
//

#include "ConnDelegate.h"
#include "GameManager.h"
#include "UIThreadTask.h"

USING_NS_CC;

void ConnDelegate::onConnect() {
    _service_connect = GameManager::getInstance()->connectService();
    _service_proto = GameManager::getInstance()->protoService();
    _task_thread = UIThreadTask::getInstance();
    log("[Info] connect connect!");
}

void ConnDelegate::onDisconnect() {
    log("[Info] connect disconnect!");
}

void ConnDelegate::onError() {
    log("[Error] connect error!");
}

void ConnDelegate::onRecv(const ByteArray& bytes) {
    ValueMap dict;
    _service_proto->decode(bytes, dict);
    _task_thread->push_proto(dict);
}
