#ifndef _PLAYER_GUN_H_
#define _PLAYER_GUN_H_

#include "cocos2d.h"

namespace gunbounce {
    class PlayerGun {
    public:
        PlayerGun(const double x, const double y, cocos2d::Scene* parentScene);
        void update();
        void tryToShoot();
    private:
        //cocos2d::Vec2 position;
        cocos2d::Sprite* gunSprite;
        //cocos2d::PhysicsBody* gunPhysBody;
    };
}

#endif // _PLAYER_GUN_H_
