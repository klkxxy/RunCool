#include "基类管理者.h"

#define ground_hight 59

USING_NS_CC;

bool 基类管理者::init(){
    if(!Node::init()){
        return false;
    }
    
    createCoin();
    
    createRock();
    
    this->scheduleUpdate();
    
    return true;
}

void 基类管理者::createCoin(){
    m_coinArr = Array::create();
    m_coinArr->retain();
    
    金币* coin = NULL;
    
    for(int i = 1; i <= coinNum; ++ i){
        coin = 金币::create();
        
        coin->setVisible(false);
        
        coin->setTag(coinTag);
        
        //º«µ√ÃÌº”
        this->addChild(coin);
        
        m_coinArr->addObject(coin);
    }/**/
}

void 基类管理者::createRock(){
    m_rockArr = Array::create();
    m_rockArr->retain();
    
    箱子* rock = NULL;
    
    float dis = 960;//¡Ω—“ Øµƒº‰æ‡
    
    for(int i = 1; i <= rockNum; ++ i){
        rock = 箱子::create();
        
        rock->setTag(rockTag);
        
        rock->setPosition(dis,ground_hight+rock->getConSize().height/2);
        dis += 640;
        
        //º«µ√ÃÌº”
        this->addChild(rock);
        
        m_rockArr->addObject(rock);
    }/**/
}

void 基类管理者::update(float dt){
    Ref* obj = NULL;
    金币* coin = NULL;
    
    //–Ë“™÷ÿ÷√Ω±“µƒ∏ˆ ˝
    int setNum = 0;
    CCARRAY_FOREACH(m_coinArr,obj){
        coin = (金币*)obj;
        
        //≤ª‘⁄∆¡ƒª
        if(coin->getPositionX() < -coin->getConSize().width/2){
            coin->setVisible(false);
        }
        
        //“™ «≤ªø…º˚£¨“™≤ªæÕ «≤ª‘⁄∆¡ƒª¿Ô£¨“™≤ªæÕ «±ª≈ˆ◊≤¡À
        if( !coin->isVisible() ){
            setNum ++;
        }
        
        //»√Ω±““∆∂Ø
        coin->setPositionX(coin->getPositionX()-4);
    }
    
    //4∏ˆ»´≤ø÷ÿ÷√
    if(setNum == 4){
        int i = 0;
        float posX = 640+50;
        float posY = ground_hight + 15 + CCRANDOM_0_1()*60;
        CCARRAY_FOREACH(m_coinArr,obj){
            coin = (金币*)obj;
            //≤ª‘⁄∆¡ƒª
            if(coin->getPositionX() < -coin->getConSize().width/2){
                coin->setVisible(false);
            }
            //“™ «≤ªø…º˚£¨“™≤ªæÕ «≤ª‘⁄∆¡ƒª¿Ô£¨“™≤ªæÕ «±ª≈ˆ◊≤¡À
            if( !coin->isVisible() ){
                //¡Ω∏ˆ¡Ω∏ˆ“ª∆
                if(i < 2){
                    posX += 30;//¡Ω∏ˆΩ±“Õ¨“ª∏ﬂ∂»£¨º‰∏Ù30
                }else{
                    //÷ÿ–¬÷ÿ÷√Œª÷√
                    i = -1;
                    posY = ground_hight + 15 + CCRANDOM_0_1()*60;
                    posX += 400;
                }
                i ++;//÷ÿ÷√Ω±“∏ˆ ˝º«¬º
                //
                coin->setVisible(true);
                coin->setPosition(posX,posY);
            }
        }
    }
    
    Ref* rockObj = NULL;
    箱子* rock = NULL;
    
    CCARRAY_FOREACH(m_rockArr,rockObj){
        rock = (箱子*)rockObj;
        
        if(rock->getPositionX() < -rock->getConSize().width/2){
            rock->setVisible(false);
        }
        if(rock->isVisible() == false){
            float posX = 1280;
            float posY = ground_hight + rock->getConSize().height/2;
            if(CCRANDOM_MINUS1_1() > 0){
                posY += 50;
            }
            rock->setPosition(posX,posY);
            rock->setVisible(true);
        }
        
        rock->setPositionX(rock->getPositionX()-4);
    }
}
