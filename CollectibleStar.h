#ifndef _COLLECTIBLE_STAR_H_
#define _COLLECTIBLE_STAR_H_

#include "cocos2d.h"

namespace gunbounce {
    class CollectibleStar {
    public:
        CollectibleStar(const float x, const float y);
    private:
        cocos2d::Sprite* shotSprite;
    };
}

#endif // _COLLECTIBLE_STAR_H_
