#ifndef __GUNBOUNCE_UTILS_H__
#define __GUNBOUNCE_UTILS_H__

#include "cocos2d.h"

namespace gunbounce {

    extern const cocos2d::Size DESIGN_RESOLUTION_SIZE;
    extern const cocos2d::Size SMALL_RESOLUTION_SIZE;
    extern const cocos2d::Size MEDIUM_RESOLUTION_SIZE;
    extern const cocos2d::Size LARGE_RESOLUTION_SIZE;

    cocos2d::Vec2 calculateNormalVecFromAngle(const float angle);
}
    
#endif // __GUNBOUNCE_UTILS_H__
