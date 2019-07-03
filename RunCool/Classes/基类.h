#ifndef __Base__H__
#define __Base__H__

#include "cocos2d.h"

class 基类 : public cocos2d::Node{
public:
    基类();
    
    void 设置精灵(cocos2d::Sprite* sprite);
    cocos2d::Sprite* 获取精灵();
    
    cocos2d::Size getConSize();
    
private:
    cocos2d::Sprite* 精灵;
};/**/

#endif
