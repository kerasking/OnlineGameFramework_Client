#include "HelloWorldScene.h"
#include <string>
#include <thread>
#include <mutex>
#include "ByteArray.h"

#include "ProtoDelegate.h"

USING_NS_CC;
using namespace std;

Scene* HelloWorld::createScene() {
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

void HelloWorld::onConnect(bool succ) {
    if(!succ) {
        log("连接失败。。。");
        return;
    }
    
    log("连接成功。。。");
    socket->asyncIO_start();
    
    // 模仿一个数据
    cocos2d::ValueMap map;
    map["id"] = Value(123);
    map["name"] = Value("十元够不够");
    map["tel"] = Value("13800000000");
    map["age"] = Value(18);
    
    // 发送
    ByteArray data(ByteEndian::BIG);
    data.clear();
    data.writeInt32(map["id"].asInt());
    //data.writeString(map["name"].asString());
    //data.writeString(map["tel"].asString());
    //data.writeInt32(map["age"].asInt());
    
    socket->async_send(data.first(), data.size(),
                       std::bind(&HelloWorld::onSend, this, std::placeholders::_1));
}

void HelloWorld::onSend(ssize_t len) {
    log("send: %ld", len);
}

void HelloWorld::onRecv(ssize_t len) {
    
}


bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(sprite, 0);
    
    
//    socket = new Socket();
//    socket->async_connect("127.0.0.1", 7464,
//                          std::bind(&HelloWorld::onConnect, this, std::placeholders::_1));
    
    ProtoDelegate proto;
    proto.loadAllProto();
    
    ValueMap data;
    data["name"] = Value("aaaa");
    data["age"] = Value(3);
    data["id"] = 123;
    
    auto bytes = proto.pack("Person_BaseInfo", data);
    auto un = proto.unpack(bytes);
    
    for(int i = 0; i < bytes.size(); i++) {
        printf("%d ", int(bytes.readInt8(i)));
    }
    printf("\n");
    
    log("%d %s %d", un["id"].asInt(), un["name"].asString().c_str(), un["age"].asInt());
    
    return true;
}

void HelloWorld::update(float dlt) {
    std::thread t([=] {
        log("send...");
        string str = "hello 世界！";
        int len = socket->send((byte*)str.c_str(), str.size());
        log("sended: %d\n", len);
    });
    t.detach();
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
