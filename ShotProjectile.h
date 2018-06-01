#ifndef _SHOT_PROJECTILE_H_
#define _SHOT_PROJECTILE_H_

#include "cocos2d.h"

namespace gunbounce {
    class ShotProjectile {
    public:
        ShotProjectile(const float x, const float y, const float angle, const float mass, const float force, cocos2d::Scene* const parentScene);
    private:
        cocos2d::Sprite* shotSprite;
        const float PHYSRADIUS;
        const float PHYSMASS;
    };
}

#endif // _SHOT_PROJECTILE_H_
