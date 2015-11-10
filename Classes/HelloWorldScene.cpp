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
    
    //scheduleUpdate();
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(sprite, 0);
    
    
    
    
//    ValueMap dict;
//    dict["_proto_name_"] = "Person_BaseInfo";
//    dict["id"] = 1;
//    dict["name"] = "aaaa";
//    dict["age"] = 18;
//    dict["gender"] = "BOY";
//    
//    ByteArray bytes(ByteEndian::BIG);
//    
//    auto game = GameManager::getInstance();
//    game->protoService()->encode(dict, bytes);
//    
//    for(int i = 0; i < bytes.size(); i++) {
//        printf("%d ", int(bytes.readInt8(i)));
//    }
//    printf("\n");
    
    //GameManager::getInstance()->sendProto(<#const cocos2d::ValueMap &dict#>);
    
    
    return true;
}

void HelloWorld::update(float dlt) {
    
}

void HelloWorld::test() {
    ValueMap data;
    ByteArray bytes(ByteEndian::BIG);
    
    data["_proto_name_"] = Value("Person_BaseInfo");
    data["id"] = 123;
    data["name"] = Value("aaaa");
    data["age"] = Value(18);
    
    ValueVector a;
    
    ValueVector a0;
    a0.push_back(Value(123));
    a0.push_back(Value(124));
    a.push_back(Value(a0));
    
    ValueVector a1;
    a1.push_back(Value(126));
    a.push_back(Value(a1));
    
    data["a"] = a;
    
    data["c"] = "NO";
    
    ValueVector d;
    d.push_back(Value(234));
    d.push_back(Value(235));
    d.push_back(Value(236));
    data["d"] = d;
    
    ValueMap testInfo;
    testInfo["tel"] = "11111";
    testInfo["addr"] = "SSSSS";
    testInfo["e"] = "BBB";
    
    data["e"] = testInfo;
    
    
    
    ProtoLoader::getInstance()->loadAllProtos();
    auto encoder = new Encoder();
    auto decoder = new Decoder();
    
    ProtoService<cocos2d::ValueMap> service(encoder, decoder);
    
    
    service.encode(data, bytes);
    
    for(int i = 0; i < bytes.size(); i++) {
        printf("%d ", int(bytes.readInt8(i)));
    }
    printf("\n");
    
    ValueMap ddd;
    service.decode(bytes, ddd);
    
    log("id: %d", ddd["id"].asInt());
    log("name: %s", ddd["name"].asString().c_str());
    log("age: %d", ddd["age"].asInt());
    
    auto da = ddd["a"].asValueVector();
    for(auto& item : da) {
        auto dda = item.asValueVector();
        for(auto& dda_item : dda) {
            log("a: %d", dda_item.asInt());
        }
    }
    
    log("c: %s", ddd["c"].asString().c_str());
    
    auto dd = ddd["d"].asValueVector();
    for(auto& item : dd) {
        log("d: %d", item.asInt());
    }
    
    auto de = ddd["e"].asValueMap();
    log("e_tel: %s", de["tel"].asString().c_str());
    log("e_addr: %s", de["addr"].asString().c_str());
    log("e_e: %s", de["e"].asString().c_str());
}
