#ifndef __BaseManager__H__
#define __BaseManager__H__

#include "cocos2d.h"
#include "金币.h"
#include "箱子.h"


#define coinNum 4
#define coinTag 2
#define rockNum 2
#define rockTag 3

class 基类管理者 : public cocos2d::Node{
public:
	CREATE_FUNC(基类管理者);
	virtual bool init();
	virtual void update(float dt);

private:
	void createCoin();
	cocos2d::Array* m_coinArr;

	void createRock();
	cocos2d::Array* m_rockArr;
};/**/

#endif
