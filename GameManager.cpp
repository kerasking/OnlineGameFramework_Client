//
//  GameManager.cpp
//  CppTest38
//
//  Created by Buwenjie on 15/10/14.
//
//

#include "GameManager.h"

#include "net/default/Encoder.h"
#include "net/default/Decoder.h"
#include "net/default/ProtoLoader.h"
#include "ConnDelegate.h"

USING_NS_CC;

GameManager::GameManager() {
    
}

GameManager* GameManager::getInstance() {
    static GameManager instance;
    return &instance;
}

void GameManager::start() {
    auto encoder = new Encoder();
    auto decoder = new Decoder();
    ProtoLoader::getInstance()->loadAllProtos();
    
    _service_proto = new ProtoService<ValueMap>(encoder, decoder);
    _service_connect = new ConnectService(new ConnDelegate());
    
    _service_connect->run("127.0.0.1", 7464);
}

void GameManager::stop() {
    _service_connect->stop();
    
    delete _service_connect;
    delete _service_proto;
}

ProtoService<cocos2d::ValueMap>* GameManager::protoService() {
    return _service_proto;
}

ConnectService* GameManager::connectService() {
    return _service_connect;
}
