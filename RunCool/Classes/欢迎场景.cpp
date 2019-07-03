//
//  MainScene.cpp
//  RunCool-mobile
//
//  Created by lx on 2019/6/10.
//

#include "欢迎场景.h"
#include "SimpleAudioEngine.h"
#include "游戏场景.h"

USING_NS_CC;
//using namespace CocosDenshion;


Scene* 欢迎场景::scene(){
    Scene* welS = Scene::create();
    Layer* lay = 欢迎场景::create();
    welS->addChild(lay);
    return welS;
}

bool 欢迎场景::init(){
    if(!Layer::init()){
        return false;
    }
    
    //preloadMusic
    initProBGM();

    //create background
    initBackGround();
    
    return true;
}

void 欢迎场景::initProBGM(){
    CocosDenshion::SimpleAudioEngine* ae = CocosDenshion::SimpleAudioEngine::getInstance();
    ae->preloadEffect("5c88d4ab26dd620216.mp3");
    ae->preloadBackgroundMusic("background.mp3");
    ae->preloadEffect("5c8b0bd8ab84596877.mp3");
}

void 欢迎场景::initBackGround(){
    auto ws = Director::getInstance()->getWinSize();
    float ww = ws.width; //获取屏幕宽度
    float wh = ws.height;//获取屏幕高度
    auto cp = Vec2(ww/2, wh/2);
    Sprite* 精灵背景 = Sprite::create("MainBG.png");
    精灵背景->setPosition(cp);
    this->addChild(精灵背景);

    
    initStartBtn();
    
}

void 欢迎场景::initStartBtn(){
    MenuItemImage* 菜单图 = MenuItemImage::create("start_n.png", "start_s.png", CC_CALLBACK_0(欢迎场景::start, this));
    Menu* 菜单 = Menu::create(菜单图, NULL);
    auto 尺寸 = Director::getInstance()->getWinSize();
    float winw = 尺寸.width; //获取屏幕宽度
    float winh = 尺寸.height;//获取屏幕高度
    菜单->setPosition(Vec2(winw/2, winh/3));
    this->addChild(菜单);
}

void 欢迎场景::start(){
   
    
    Scene* 游戏场景 = TransitionFade::create(1, 游戏场景::createScene());
    Director::getInstance()->replaceScene(游戏场景);
}
