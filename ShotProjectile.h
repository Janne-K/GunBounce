#ifndef _SHOT_PROJECTILE_H_
#define _SHOT_PROJECTILE_H_

#include "cocos2d.h"

namespace gunbounce {
    class ShotProjectile {
    public:
        ShotProjectile(const float x, const float y, const float angle, const float force, cocos2d::Layer* const parentLayer);
        cocos2d::Sprite* getSprite();
    private:
        cocos2d::Sprite* shotSprite;
    };
}

#endif // _SHOT_PROJECTILE_H_
