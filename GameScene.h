#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "PlayerGun.h"

namespace gunbounce {
    class GunBounce : public cocos2d::Scene
    {
    public:
        static cocos2d::Scene* createScene();

        virtual bool init();
        
        // a selector callback
        void menuCloseCallback(cocos2d::Ref* pSender);
        
        // implement the "static create()" method manually
        CREATE_FUNC(GunBounce);
    private:
        std::shared_ptr<PlayerGun> player;
        cocos2d::EventListenerMouse* mouseListener;
        cocos2d::EventListenerTouchOneByOne* touchListener;
    };
}
#endif // __GAME_SCENE_H__
