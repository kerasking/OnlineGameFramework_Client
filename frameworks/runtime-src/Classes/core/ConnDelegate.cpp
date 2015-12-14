//
//  ConnDelegate.cpp
//  OnlineGameFramework_Client
//
//  Created by Buwenjie on 15/10/20.
//
//

#include "ConnDelegate.h"
#include "GameManager.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace red;

void ConnDelegate::onConnect() {
    log("[CPP] connect connect!");
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("CONNECT");
}

void ConnDelegate::onDisconnect() {
    log("[CPP] connect disconnect!");
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("DISCONNECT");
}

void ConnDelegate::onError() {
    log("[CPP] connect error!");
    // 在主线程中结束，避免死锁
    UIThreadTask::getInstance()->push_task([]() {
        GameManager::getInstance()->stop();
    });
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("CONNECT_ERROR");
}

void ConnDelegate::onRecv(const ByteArray& bytes) {
    ValueMap dict;
    GameManager::getInstance()->protoService()->decode(bytes, dict);
    UIThreadTask::getInstance()->push_proto(dict);
}
