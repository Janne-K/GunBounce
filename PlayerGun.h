#ifndef _PLAYER_GUN_H_
#define _PLAYER_GUN_H_

#include "cocos2d.h"

namespace gunbounce {
    class PlayerGun {
    public:
        PlayerGun(const float x, const float y, const float pmass, const float pradius, const float rrate, cocos2d::Layer* parentLayer);
        bool canShoot();
        cocos2d::Sprite* getSprite();
    private:
        cocos2d::Sprite* gunSprite;
        const float PHYSRADIUS;
        const float PHYSMASS;
        const float ROTATIONRATE;
        void shoot();
        void getHit();
    };
}

#endif // _PLAYER_GUN_H_
