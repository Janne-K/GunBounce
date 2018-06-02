#ifndef _SHOT_PROJECTILE_H_
#define _SHOT_PROJECTILE_H_

#include "cocos2d.h"

namespace gunbounce {
    class ShotProjectile {
    public:
        ShotProjectile(const float x, const float y, const float angle, const float mass, const float force, const float ltime, cocos2d::Scene* const parentScene);
        float getLifeTime();
        void decreaseLifeTime(float amount);
        cocos2d::Sprite* getSprite();
    private:
        cocos2d::Sprite* shotSprite;
        const float PHYSRADIUS;
        const float PHYSMASS;
        float lifetime;
    };
}

#endif // _SHOT_PROJECTILE_H_
