#ifndef _PLAYER_GUN_H_
#define _PLAYER_GUN_H_

#include "cocos2d.h"

namespace gunbounce {
    class PlayerGun {
    public:
        PlayerGun(const float x, const float y, cocos2d::Layer* parentLayer);
        bool canShoot();
        cocos2d::Sprite* getSprite();
    private:
        cocos2d::Sprite* gunSprite;
    };
}

#endif // _PLAYER_GUN_H_
