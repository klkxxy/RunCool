#ifndef __GameOver__H__
#define __GameOver__H__

#include "cocos2d.h"
#include "本地存储.h"

USING_NS_CC;

class 游戏结束 : cocos2d::Layer{
public:
	virtual bool init();
	static cocos2d::Scene* scene();
	CREATE_FUNC(游戏结束);

	void 创建背景();
    void 创建新纪录();
	void 再来一局的事件(cocos2d::Object *sneder);
    void 创建分数框();
    void 截取屏幕保存至手机相册中();
private:
    
};/**/

#endif
