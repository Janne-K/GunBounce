#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "PlayerGun.h"
#include "ShotProjectile.h"
#include "GunBounceUtils.h"
#include "CollectibleStar.h"

namespace gunbounce {
    class GunBounce : public cocos2d::Scene
    {
    public:
        static cocos2d::Scene* createScene();

        virtual bool init();
        virtual void update(float delta);
        
        // a selector callback
        void menuCloseCallback(cocos2d::Ref* pSender);
        
        // implement the "static create()" method manually
        CREATE_FUNC(GunBounce);
        
        void addShotToList(std::shared_ptr<ShotProjectile> shotToAdd);
    private:
        std::shared_ptr<PlayerGun> player;
        std::vector<std::shared_ptr<ShotProjectile>> shots;
        cocos2d::EventListenerMouse* mouseListener;
        cocos2d::EventListenerTouchOneByOne* touchListener;
        void playerShoot();
        void createPlayer();
    };
}
#endif // __GAME_SCENE_H__
