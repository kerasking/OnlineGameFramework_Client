//
//  ConnDelegate.cpp
//  OnlineGameFramework_Client
//
//  Created by Buwenjie on 15/10/20.
//
//

#include "ConnDelegate.h"
#include "GameManager.h"

USING_NS_CC;

ConnDelegate::ConnDelegate()
: _task_conn(nullptr)
, _task_disconn(nullptr)
, _task_err(nullptr) {
    
}

void ConnDelegate::onConnect() {
    log("[Info] connect connect!");
    
    if(_task_conn) {
        UIThreadTask::getInstance()->push_task(_task_conn);
    }
}

void ConnDelegate::onDisconnect() {
    log("[Info] connect disconnect!");
    
    if(_task_disconn) {
        UIThreadTask::getInstance()->push_task(_task_conn);
    }
}

void ConnDelegate::onError() {
    log("[Error] connect error!");
    
    if(_task_err) {
        UIThreadTask::getInstance()->push_task(_task_err);
    }
}

void ConnDelegate::onRecv(const ByteArray& bytes) {
    ValueMap dict;
    GameManager::getInstance()->protoService()->decode(bytes, dict);
    UIThreadTask::getInstance()->push_proto(dict);
}

void ConnDelegate::bindConnect(Task t) {
    _task_conn = t;
}

void ConnDelegate::bindDisconnect(Task t) {
    _task_disconn = t;
}

void ConnDelegate::bindError(Task t) {
    _task_err = t;
}
