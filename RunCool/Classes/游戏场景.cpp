//
//  PlayScene.cpp
//  RunCool-mobile
//
//  Created by lx on 2019/6/10.
//

#include "游戏场景.h"
#include "SimpleAudioEngine.h"
#include "游戏结束.h"

#define 地板高度 58
#define 跑者的x坐标 80

USING_NS_CC;

Scene* 游戏场景::createScene(){
    //创建带有物理的Scene
    auto 场景 = Scene::createWithPhysics();
    Vect 重力 = Vect(0,-900);
    场景->getPhysicsWorld()->setGravity(重力);
    //开启调试,将物理世界描绘出来，使得其可见
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    //Layer  注意这里要用 auto ，不然setPhysicsWorld不可以用
    auto 布局 = 游戏场景::create();
    布局->setPhysicsWorld(场景->getPhysicsWorld());
    场景->addChild(布局);
    return 场景;

}

bool 游戏场景::init(){
    if(!Layer::init()){
        return false;
    }
    if(CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() == false){
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("background.mp3",true);
    }
    
    this->分数 = 0;
    
    this->是否结束 = false;
    
    初始化物理世界();
    
    初始化背景();
    
    //该定时器默认刷新次数与屏幕刷新频率有关。如频率为60帧每秒，那么scheduleUpdate每秒执行60次刷新。
    //与scheduleUpdate其对应的刷新函数体为update()，即每一帧会执行一次update()函数。
    this->scheduleUpdate();
    
    跑者 = 跑酷者::create();
    跑者->setPosition(跑者的x坐标,地板高度+跑者->获取跑者跳跃的尺寸().height/2);
    跑者->跑步();
    this->addChild(跑者);
    
    基类管理 = 基类管理者::create();
    this->addChild(基类管理);

    创建跳跃按钮();
    
    创建蹲下按钮();
    
    创建得分栏();

    return true;
}

void 游戏场景::创建得分栏(){
    auto 屏幕尺寸 = Director::getInstance()->getVisibleSize();
    得分栏lab = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
    得分栏lab->setPosition(120, 屏幕尺寸.height-60);
    this->addChild(得分栏lab);
}


void 游戏场景::初始化物理世界(){
    auto 屏幕尺寸 = Director::getInstance()->getVisibleSize();
    auto 屏幕坐标 = Director::getInstance()->getVisibleOrigin();
    
    auto 物理刚体 = PhysicsBody::createEdgeSegment(屏幕坐标, Vec2(屏幕尺寸.width, 0),PHYSICSBODY_MATERIAL_DEFAULT,1);

    auto 关联 = Node::create();
    
    关联->setPhysicsBody(物理刚体);
    
    关联->setPosition(0,地板高度);

    this->addChild(关联);
    
    
}

void 游戏场景::初始化背景(){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    //背景1
    背景精灵1 = Sprite::create("Map00.png");
    背景精灵1->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(背景精灵1);
    
    //地面1
    地板精灵1 = Sprite::create("Ground00.png");
    地板精灵1->setPosition(visibleSize.width/2,地板精灵1->getContentSize().height/2);
    this->addChild(地板精灵1);
    
    //背景2
    背景精灵2 = Sprite::create("Map01.png");
    背景精灵2->setPosition(背景精灵1->getContentSize().width+visibleSize.width/2,visibleSize.height/2);
    this->addChild(背景精灵2);
    
    //地面2
    地板精灵2 = Sprite::create("Ground01.png");
    地板精灵2->setPosition(背景精灵1->getContentSize().width+visibleSize.width/2,地板精灵2->getContentSize().height/2);
    this->addChild(地板精灵2);
    
}

//每一次更新，往左移动两个像素
void 游戏场景::update(float dt){
    int posX1 = 背景精灵1->getPositionX();
    int posX2 = 背景精灵2->getPositionX();
    
    posX1 -= 4;
    posX2 -= 4;
    
    分数 ++;
    得分栏lab->setString(String::createWithFormat("Current Score:%d",分数)->getCString());
    
    auto mapSize = 背景精灵1->getContentSize();
    
    if(posX1 < -mapSize.width/2){
        posX1 = mapSize.width + mapSize.width/2;
        posX2 = mapSize.width/2;
    }
    if(posX2 < -mapSize.width/2){
        posX2 = mapSize.width + mapSize.width/2;
        posX1 = mapSize.width/2;
    }
    
    背景精灵1->setPositionX(posX1);
    背景精灵2->setPositionX(posX2);
    地板精灵1->setPositionX(posX1);
    地板精灵2->setPositionX(posX2);
}

void 游戏场景::创建跳跃按钮(){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto jumpLabel = Label::create("Jump","Arail",30);
    auto norBtn = Scale9Sprite::create("closenormal2.png");
    auto lightBtn = Scale9Sprite::create("CloseNormal.png");
    
    auto jumpBtn = ControlButton::create(jumpLabel,norBtn);
    jumpBtn->setPosition(visibleSize.width-80,130);
    jumpBtn->setBackgroundSpriteForState(lightBtn,Control::State::HIGH_LIGHTED);
    
    jumpBtn->addTargetWithActionForControlEvents(
                                                 this,
                                                 cccontrol_selector(游戏场景::跳跃事件),
                                                 Control::EventType::TOUCH_DOWN);
    
    this->addChild(jumpBtn);
}


void 游戏场景::跳跃事件(Ref* pSender,Control::EventType event){
    
    跑者->跳跃();
}

void 游戏场景::创建蹲下按钮(){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    auto crouchLabel = Label::create("Crouch","Arail",30);
    auto norBtn = Scale9Sprite::create("closenormal2.png");
    auto lightBtn = Scale9Sprite::create("CloseNormal.png");
    
    auto crouchBtn = ControlButton::create(crouchLabel,norBtn);
    crouchBtn->setPosition(visibleSize.width-100,80);
    crouchBtn->setBackgroundSpriteForState(lightBtn,Control::State::HIGH_LIGHTED);
    
    //
    crouchBtn->addTargetWithActionForControlEvents(
                                                   this,
                                                   cccontrol_selector(游戏场景::蹲下事件),
                                                   Control::EventType::TOUCH_DOWN);
    
    //
    crouchBtn->addTargetWithActionForControlEvents(
                                                   this,
                                                   cccontrol_selector(游戏场景::站起来事件),
                                                   Control::EventType::TOUCH_UP_INSIDE);
    
    this->addChild(crouchBtn);
}
void 游戏场景::蹲下事件(Ref* pSender,Control::EventType event){
    if(跑者->获取跑者状态() == running){
        跑者->蹲下();
        跑者->setPosition(跑者的x坐标,地板高度+跑者->获取跑者蹲下的尺寸().height/2);
    }
}
void 游戏场景::站起来事件(Ref* pSender,Control::EventType event){
    if(跑者->获取跑者状态() == crouch){
        跑者->stopAllActions();
        跑者->跑步();
        跑者->setPosition(跑者的x坐标,地板高度+跑者->获取跑者跳跃的尺寸().height/2);
    }
}

void 游戏场景::onEnter(){
    Layer::onEnter();
    auto 监听 = EventListenerPhysicsContact::create();
    
    监听->onContactBegin = CC_CALLBACK_1(游戏场景::onContactBegin,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(监听,this);
}
void 游戏场景::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListenersForTarget(this);
}
bool 游戏场景::onContactBegin(PhysicsContact& contact){
    auto 刚体1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
    auto 刚体2 = (Sprite*)contact.getShapeB()->getBody()->getNode();

    if((刚体1->getTag() == 3 && 刚体2->getTag() == 1) ||
       (刚体1->getTag() == 1 && 刚体2->getTag() == 3) ){
        
        if (!this->是否结束) {
            this->是否结束 = true;
            游戏结束事件();
        }
        
    }
    
    if(刚体1->getTag() == 2){
        刚体1->setVisible(false);
    }
    if(刚体2->getTag() == 2){
        刚体2->setVisible(false);
    }
    
    return false;
}

void 游戏场景::游戏结束事件(){

    本地存储::getInstance()->saveIntegerToUserDefault("this_score",this->分数);
    
    Director::getInstance()->replaceScene(游戏结束::scene());
    
}


