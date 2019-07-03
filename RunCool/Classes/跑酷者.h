
#include "cocos2d.h"

enum runnerState{
    running,
    jumpUp,
    jumpDown,
    crouch
};


class 跑酷者 : public cocos2d::Node{
public:
    virtual bool init();
    CREATE_FUNC(跑酷者);
    
    void 初始化物理刚体();//初始化物理刚体

    //初始化 action 集合
    void 初始化动作集合(cocos2d::SpriteFrameCache* frameCache);

    //根据动作名称执行动作
    void 根据动作名称执行动作(const char* actionName);//
    
    void 跑步();
    
    void 跳跃();
    
    void 蹲下();
    
    virtual void update(float dt);
    
    cocos2d::Size 获取跑者跳跃的尺寸(){ return 跑和跳的大小;};
    cocos2d::Size 获取跑者蹲下的尺寸() { return 蹲下来的大小;};
    runnerState 获取跑者状态(){ return 跑者状态;};
private:
    //  需要一个主要的精灵执行动作
    cocos2d::Sprite* 跑者;
    
    // 不同的动作需要不同的刚体大小
    cocos2d::Size 跑和跳的大小;//跑和跳的大小一样
    cocos2d::Size 蹲下来的大小;//蹲下来的大小
    
    runnerState 跑者状态;
};




