#include "cocos2d.h"
#include "跑酷者.h"
#include "cocos-ext.h"
#include "基类管理者.h"
#include "本地存储.h"

USING_NS_CC_EXT;

class 游戏场景 : public cocos2d::Layer{
public:
    virtual bool init();
    static cocos2d::Scene* createScene();
    CREATE_FUNC(游戏场景);

    cocos2d::PhysicsWorld* 物理世界;
    void setPhysicsWorld(cocos2d::PhysicsWorld* world){ 物理世界 = world;};/**/

    //初始化背景
    void 初始化背景();
    //用update函数让地图滚动
    virtual void update(float dt);

    //Jump
    void 创建跳跃按钮();
    void 跳跃事件(Ref* pSender,Control::EventType event);

    //Crouch
    void 创建蹲下按钮();
    void 蹲下事件(Ref* pSender,Control::EventType event);
    void 站起来事件(Ref* pSender,Control::EventType event);


    void onEnter();
    void onExit();
    bool onContactBegin(cocos2d::PhysicsContact& contact);

    void 游戏结束事件();
    void 创建得分栏();
private:

    void 初始化物理世界();

    跑酷者* 跑者;

    //背景精灵
    cocos2d::Sprite* 背景精灵1;
    cocos2d::Sprite* 背景精灵2;
    cocos2d::Sprite* 地板精灵1;
    cocos2d::Sprite* 地板精灵2;

    cocos2d::Label* 得分栏lab;
    
    int 分数;
    
    基类管理者* 基类管理;
    
    bool 是否结束;
};
