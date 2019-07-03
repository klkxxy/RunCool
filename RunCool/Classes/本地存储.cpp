#include "本地存储.h"

本地存储::本地存储()
{
}

本地存储::~本地存储()
{
}

bool 本地存储::init(){
	return true;
}

本地存储* 本地存储::shareUserRecord = nullptr;

本地存储* 本地存储::getInstance(){
	if(shareUserRecord == NULL){
		shareUserRecord = new 本地存储();
		if(!shareUserRecord->init()){
			delete(shareUserRecord);
			shareUserRecord = NULL;
		}
	}
	return shareUserRecord;
}

void 本地存储::saveIntegerToUserDefault(const char* key, int score){
	UserDefault::getInstance()->setIntegerForKey(key,score);	
}


int 本地存储::readIntegerFromUserDefault(const char* key){
	int score = UserDefault::getInstance()->getIntegerForKey(key);
	return score;
}
