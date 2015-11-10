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

USING_NS_CC;

GameManager::GameManager()
: _service_proto(nullptr)
, _service_connect(nullptr)
, _delegate_conn(nullptr) {
    
}

GameManager* GameManager::getInstance() {
    static GameManager instance;
    return &instance;
}

void GameManager::init() {
    auto encoder = new Encoder();
    auto decoder = new Decoder();
    ProtoLoader::getInstance()->loadAllProtos();
    
    _delegate_conn = new ConnDelegate();
    _service_proto = new ProtoService<ValueMap>(encoder, decoder);
    _service_connect = new ConnectService(_delegate_conn);
}

void GameManager::start() {
    _service_connect->run("127.0.0.1", 7464);
}

void GameManager::stop() {
    _service_connect->stop();
    
    delete _service_connect;
    _service_connect = nullptr;
    
    delete _service_proto;
    _service_proto = nullptr;
    
    delete _delegate_conn;
    _delegate_conn = nullptr;
}

void GameManager::sendProto(const ValueMap& dict) {
    ByteArray bytes(ByteEndian::BIG);
    _service_proto->encode(dict, bytes);
    _service_connect->sendProto(bytes);
}

ProtoService<cocos2d::ValueMap>* GameManager::protoService() {
    return _service_proto;
}

ConnectService* GameManager::connectService() {
    return _service_connect;
}

ConnDelegate* GameManager::connDelegate() {
    return _delegate_conn;
}
