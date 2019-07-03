//
//  Coin.cpp
//  RunCool-mobile
//
//  Created by lx on 2019/6/10.
//

#include "金币.h"
USING_NS_CC;

bool 金币::init(){
    if(!Node::init()){
        return false;
    }

    //缓存池
    auto 缓存池 = SpriteFrameCache::getInstance();
    缓存池->addSpriteFramesWithFile("parkour.plist","parkour.png");

    auto 精灵 = Sprite::createWithSpriteFrameName("coin0.png");

    //绑定
    设置精灵(精灵);
    //执行动作
    获取精灵()->runAction(创建金币动作(缓存池));
    //绑定刚体
    物理刚体();

    return true;
}

Animate* 金币::创建金币动作(SpriteFrameCache* frameCache){
    
    SpriteFrame* frame = NULL;
    //数组不行 要用vector
    //auto frameArray = Array::create();
    //frameArray->retain();
    Vector<SpriteFrame*>精灵布局数组;

    // 用一个列表保存所有SpriteFrame对象
    for(int i = 0; i <= 7; i++) {
            /* 从SpriteFrame缓存池中获取CCSpriteFrame对象 */
        frame = frameCache->spriteFrameByName(String::createWithFormat("coin%d.png", i)->getCString());
        精灵布局数组.pushBack(frame);
      
    }
    /* 使用SpriteFrame列表创建动画对象 */
    auto 动画对象 = Animation::createWithSpriteFrames(精灵布局数组);

    动画对象->setLoops(-1);

    动画对象->setDelayPerUnit(0.1f);

    /* 将动画包装成一个动作 */
    auto 动作 = Animate::create(动画对象);

    return 动作;
}

void 金币::物理刚体(){
        auto 刚体 = PhysicsBody::createEdgeBox(获取精灵()->getContentSize());
        刚体->setCategoryBitmask(1);
        刚体->setCollisionBitmask(1);
        刚体->setContactTestBitmask(1);
    
        this->setPhysicsBody(刚体);
}






