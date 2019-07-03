#include "基类.h"
#include "cocos2d.h"

class 箱子 : public 基类{
public:
        virtual bool init();
        CREATE_FUNC(箱子);
    
        void 创建刚体();
};/**/

