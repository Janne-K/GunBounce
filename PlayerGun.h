#ifndef _PLAYER_GUN_H_
#define _PLAYER_GUN_H_

#include "cocos2d.h"

namespace gunbounce {
    class PlayerGun {
    public:
        PlayerGun(const float x, const float y, cocos2d::Scene* scene);
        void tryToShoot();
    private:
        cocos2d::Scene * const parentScene; // We need this to add shots to the scene
        cocos2d::Sprite* gunSprite;
        const float PHYSRADIUS;
        const float PHYSMASS;
        const float PHYSSHOOTFORCE;
        const float ROTATIONRATE;
        void shoot();
    };
}

#endif // _PLAYER_GUN_H_
