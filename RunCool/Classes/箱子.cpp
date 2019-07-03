#include "箱子.h"

USING_NS_CC;

bool 箱子::init(){
        if(!Node::init()){
                return false;
            }
    
        auto 缓存池 = SpriteFrameCache::getInstance();
        缓存池->addSpriteFramesWithFile("parkour.plist","parkour.png");
    
        auto 精灵 = Sprite::createWithSpriteFrameName("rock.png");
    
        设置精灵(精灵);
    
        创建刚体();
    
        return true;
}

void 箱子::创建刚体(){
        auto 刚体 = PhysicsBody::createEdgeBox(获取精灵()->getContentSize());
        刚体->setCategoryBitmask(1);
        刚体->setCollisionBitmask(1);
        刚体->setContactTestBitmask(1);
    
        this->setPhysicsBody(刚体);
}




