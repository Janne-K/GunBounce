#ifndef _COLLECTIBLE_STAR_H_
#define _COLLECTIBLE_STAR_H_

#include "cocos2d.h"

namespace gunbounce {
    class CollectibleStar {
    public:
        CollectibleStar(const float x, const float y, cocos2d::Layer* parentLayer);
        void setNewPosition(const float x, const float y);
        cocos2d::Sprite* getSprite();
    private:
        cocos2d::Sprite* starSprite;
    };
}

#endif // _COLLECTIBLE_STAR_H_
