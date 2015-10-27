#include "HelloWorldScene.h"
#include <string>
#include <thread>
#include <mutex>
#include "ByteArray.h"

#include "GameManager.h"
#include "UIThreadTask.h"

#include "net/service/ProtoService.hpp"
#include "net/default/Encoder.h"
#include "net/default/Decoder.h"
#include "net/default/ProtoLoader.h"

USING_NS_CC;
using namespace std;

Scene* HelloWorld::createScene() {
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}


bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // 启动游戏。临时写在此处
    //GameManager::getInstance()->start();
    
    //scheduleUpdate();
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(sprite, 0);
    
    ValueMap data;
    ByteArray bytes(ByteEndian::BIG);
    
    data["_proto_name_"] = Value("Person_BaseInfo");
    data["id"] = 123;
    data["name"] = Value("aaaa");
    data["age"] = Value(5);
    
    ValueVector a;
    
    ValueVector a0;
    a0.push_back(Value(123));
    a0.push_back(Value(124));
    a0.push_back(Value(125));
    a.push_back(Value(a0));
    
    ValueVector a1;
    a1.push_back(Value(126));
    a1.push_back(Value(127));
    a.push_back(Value(a1));
    
    data["a"] = a;
    
    data["c"] = "YES";
    
    ValueVector d;
    d.push_back(Value(234));
    d.push_back(Value(235));
    d.push_back(Value(236));
    d.push_back(Value(237));
    data["d"] = d;
    
    ProtoLoader::getInstance()->loadAllProtos();
    auto encoder = new Encoder();
    auto decoder = new Decoder();
    
    ProtoService<cocos2d::ValueMap> service(encoder, decoder);
    
    service.encode(data, bytes);
    
    for(int i = 0; i < bytes.size(); i++) {
        printf("%d ", int(bytes.readInt8(i)));
    }
    printf("\n");
    
    return true;
}

void HelloWorld::update(float dlt) {
    auto protos = UIThreadTask::getInstance()->pop_protos();
    for(auto& proto : protos) {
        auto dict = proto.asValueMap();
        for(auto& key : dict) {
            log("key: %s", key.first.c_str());
        }
    }
}
