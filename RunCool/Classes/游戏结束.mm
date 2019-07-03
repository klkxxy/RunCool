#include "游戏结束.h"
#include "欢迎场景.h"
#include "游戏场景.h"

#ifdef __OBJC__
#include "Screenshots.h"
#endif

USING_NS_CC;

Scene* 游戏结束::scene(){
	Scene* 场景 = Scene::create();
	Layer* 布局 = 游戏结束::create();
	场景->addChild(布局);
	return 场景;
}

bool 游戏结束::init(){
	if(!Layer::init()){
		return false;
	}
	//create background
	创建背景();
    
    创建分数框();
    
	return true;
}

void 游戏结束::截取屏幕保存至手机相册中(){

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Screenshots *screenshots = [[Screenshots alloc]init];
    [screenshots saveImage];
#endif

}


void 游戏结束::创建分数框(){
    
    int 最高分 = 本地存储::getInstance()->readIntegerFromUserDefault("best_score");
    int 本局得分 = 本地存储::getInstance()->readIntegerFromUserDefault("this_score");
    //update the best score
    if(本局得分 > 最高分){
        截取屏幕保存至手机相册中();
        本地存储::getInstance()->saveIntegerToUserDefault("best_score",本局得分);
        
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto scoreLab = Label::createWithTTF(String::createWithFormat("Current Score:%d",本局得分)->getCString(), "fonts/arial.ttf", 24);
    scoreLab->setColor(cocos2d::Color3B::BLACK);
    scoreLab->setPosition(120, visibleSize.height-60);
    this->addChild(scoreLab);
    
    auto hiScoreLab = Label::createWithTTF(String::createWithFormat("Best Score:%d",最高分)->getCString(), "fonts/arial.ttf", 24);
    hiScoreLab->setColor(cocos2d::Color3B::BLACK);
    hiScoreLab->setPosition(120, visibleSize.height-90);
    this->addChild(hiScoreLab);
    
    
}




void 游戏结束::创建背景(){
	auto 屏幕尺寸 = Director::getInstance()->getWinSize();
	auto 中心点 = ccp(屏幕尺寸.width / 2, 屏幕尺寸.height / 2);

	//BG
	Sprite* 背景精灵 = Sprite::create("MainBG.png");
	背景精灵->setPosition(中心点);
	this->addChild(背景精灵);

	//create button//Start mutton
	MenuItemImage* 菜单图 = MenuItemImage::create(
		"restart_n.png",
		"restart_s.png",
		CC_CALLBACK_1(游戏结束::再来一局的事件,this));

	Menu* 菜单 = Menu::create(菜单图,NULL);

	菜单->setPosition(中心点);

	this->addChild(菜单);
}

void 游戏结束::再来一局的事件(cocos2d::Object *sneder){
	CCLOG("game is restart !");
	Scene* 游戏场景 = TransitionFade::create(1,游戏场景::createScene());
	Director::getInstance()->replaceScene(游戏场景);
}
