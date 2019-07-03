//
//  MainScene.hpp
//  RunCool-mobile
//
//  Created by lx on 2019/6/10.
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include "cocos2d.h"

class 欢迎场景 : cocos2d::Layer{
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(欢迎场景);
    
private:
    //
    void initBackGround();
    //
    void initStartBtn();
    //
    void initProBGM();
    //menu start the game
    void start();
};

#endif /* MainScene_hpp */
