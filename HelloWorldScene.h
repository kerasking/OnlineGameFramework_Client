#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Socket.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);
    void update(float dlt);
    
    CREATE_FUNC(HelloWorld);
    
private:
    Socket* socket;
    
    void onConnect(bool succ);
    void onSend(ssize_t len);
    void onRecv(ssize_t len);
};

#endif // __HELLOWORLD_SCENE_H__
