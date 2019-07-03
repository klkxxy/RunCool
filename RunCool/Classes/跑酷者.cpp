//
//  Runner.cpp
//  RunCool-mobile
//
//  Created by lx on 2019/6/10.
//

#include "跑酷者.h"

USING_NS_CC;

bool 跑酷者::init(){
    
    auto frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("parkour.plist","parkour.png");
    
    跑者 = Sprite::createWithSpriteFrameName("runner0.png");

    跑和跳的大小 = 跑者->getContentSize();
    蹲下来的大小 = Sprite::createWithSpriteFrameName("runnerCrouch0.png")->getContentSize();
    
    this->addChild(跑者);
    
    初始化动作集合(frameCache);
    
    跑者状态 = running;

    初始化物理刚体();
    
    this->scheduleUpdate();
    
    this->setTag(1);
    
    return true;
}


void 跑酷者::初始化动作集合(SpriteFrameCache* frameCache){
    SpriteFrame* 布局 = NULL;
    //数组 3.0中改用vector 而不是用Array
    Vector<SpriteFrame*>布局数组;
    
    /* 1.----------------加载跑动的Animation-----------------*/
    for(int i = 0; i <= 7; i ++) {
        //从缓存池中加载精灵到Vector
        布局 = frameCache->spriteFrameByName(String::createWithFormat("runner%d.png",i)->getCString());
        布局数组.pushBack(布局);
    }
    
    //用vector里面的SpriteFrame列表创建Animation  以及设置一些参数
    auto 跑步动作 = Animation::createWithSpriteFrames(布局数组,0.1f,-1);
    //将跑动的 Animation 取名为 running
    AnimationCache::getInstance()->addAnimation(跑步动作,"running");
    
    布局数组.clear();
    for (int i=0; i<=3; i++) {
        布局 = frameCache->spriteFrameByName(String::createWithFormat("runnerJumpUp%d.png",i)->getCString());
        布局数组.pushBack(布局);

    }
    auto 跳跃动作 = Animation::createWithSpriteFrames(布局数组,0.2);//不设置无限循环
    AnimationCache::getInstance()->addAnimation(跳跃动作,"jumpUp");

    /*------------------加载跳跃过程中下落的动画----------------------------*/
    布局数组.clear();
    for(int i = 0; i <= 1; i ++){
        布局 = frameCache->spriteFrameByName(String::createWithFormat("runnerJumpDown%d.png",i)->getCString());
        布局数组.pushBack(布局);
    }
    auto 下落的动作 = Animation::createWithSpriteFrames(布局数组,0.3);
    AnimationCache::getInstance()->addAnimation(下落的动作,"jumpDown");
    
    /*------------------加载下蹲-------------------------------------------*/
    布局数组.clear();
    布局 = frameCache->spriteFrameByName("runnerCrouch0.png");
    布局数组.pushBack(布局);
    auto 蹲下动作 = Animation::createWithSpriteFrames(布局数组,0.3);//不设置无限循环
    AnimationCache::getInstance()->addAnimation(蹲下动作,"crouch");
    
}

void 跑酷者::初始化物理刚体(){
    Size 刚体尺寸;
    if (跑者状态 == crouch) {
        刚体尺寸 = 蹲下来的大小;
    }else{
        刚体尺寸 = 跑和跳的大小;
    }
    
    auto 跑者刚体 = PhysicsBody::createBox(刚体尺寸);
    
    跑者刚体->setCategoryBitmask(1);
    跑者刚体->setCollisionBitmask(1);
    跑者刚体->setContactTestBitmask(1);
    
    this->setPhysicsBody(跑者刚体);
}

void 跑酷者::跑步(){
    跑者状态 = running;
    初始化物理刚体();
    根据动作名称执行动作("running");
}

void 跑酷者::跳跃(){
    if (跑者状态 == running) {
        跑者状态 = jumpUp;
        this->getPhysicsBody()->setVelocity(Vect(0, 500));
        跑者->stopAllActions();
        根据动作名称执行动作("jumpUp");
    }
    
}

void 跑酷者::update(float dt){
    auto 加速度 = this->getPhysicsBody()->getVelocity();
    if(跑者状态 == jumpUp){
        if(加速度.y < 0.1){
            跑者状态 = jumpDown;
            跑者->stopAllActions();
            根据动作名称执行动作("jumpDown");
        }
    }
    
    if(跑者状态 == jumpDown){
        CCLOG("%f",加速度.y);
        //不应该是 等于 0
        if(加速度.y > 0){
            跑者状态 = running;
            跑者->stopAllActions();
            根据动作名称执行动作("running");
        }
    }
}

void 跑酷者::蹲下(){
    //只能在跑动的时候蹲下
    if(跑者状态 == running){
        跑者状态 = crouch;
        跑者->stopAllActions();
        初始化物理刚体();
        根据动作名称执行动作("crouch");
    }
}

void 跑酷者::根据动作名称执行动作(const char* actionName){
    auto 动作 = AnimationCache::getInstance()->animationByName(actionName);
    auto 动作吧 = Animate::create(动作);
    跑者->runAction(动作吧);
}

