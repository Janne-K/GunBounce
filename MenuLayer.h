#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__

#include "cocos2d.h"
#include "GunBounceUtils.h"

namespace gunbounce {
    class MenuLayer : public cocos2d::Layer
    {
    public:
        virtual bool init();
        CREATE_FUNC(MenuLayer);
    private:
        void menuCloseCallback(cocos2d::Ref* pSender);
        void returnToGameCallback(cocos2d::Ref* pSender);
    };
}
#endif // __MENU_LAYER_H__
