//
//  TitleScene.h
//  CppTest38
//
//  Created by Buwenjie on 15/11/9.
//
//

#ifndef TitleScene_h
#define TitleScene_h

#include <stdio.h>

class TitleScene : public cocos2d::Scene
{
public:
    virtual bool init();
    virtual void update(float dlt);
    
    CREATE_FUNC(TitleScene);
    
private:
    
};

#endif /* TitleScene_h */
