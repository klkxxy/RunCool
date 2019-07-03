//
//  Coin.hpp
//  RunCool-mobile
//
//  Created by lx on 2019/6/10.
//

#include "基类.h"

class 金币 : public 基类{
public:
    virtual bool init();
    CREATE_FUNC(金币);

    //金币动作
    cocos2d::Animate* 创建金币动作(cocos2d::SpriteFrameCache* frameCache);
    //物理刚体
    void 物理刚体();
    
private:
};/**/

