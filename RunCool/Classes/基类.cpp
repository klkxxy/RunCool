#include "基类.h"

USING_NS_CC;

基类::基类(){
    精灵 = NULL;
}

void 基类::设置精灵(Sprite* sprite){
    精灵 = sprite;

    this->addChild(精灵);
}

Sprite* 基类::获取精灵(){
    return 精灵;
}

Size 基类::getConSize(){
    return 精灵->getContentSize();
}
