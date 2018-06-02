#ifndef __GUNBOUNCE_UTILS_H__
#define __GUNBOUNCE_UTILS_H__

#include "cocos2d.h"

namespace gunbounce {

    extern const cocos2d::Size DESIGN_RESOLUTION_SIZE;
    extern const cocos2d::Size SMALL_RESOLUTION_SIZE;
    extern const cocos2d::Size MEDIUM_RESOLUTION_SIZE;
    extern const cocos2d::Size LARGE_RESOLUTION_SIZE;
    
    extern const float PLAYERPHYSRADIUS;
    extern const float PLAYERPHYSMASS;
    extern const float PLAYERPHYSSHOOTFORCE;
    extern const float PLAYERROTATIONRATE;
    extern const float PLAYERVELOCITYLIMIT;
    extern const float SHOTLIFETIME;
    
    extern const int COLL_PLAYER;
    extern const int COLL_SHOT;

    cocos2d::Vec2 calculateNormalVecFromAngle(const float angle);
}
    
#endif // __GUNBOUNCE_UTILS_H__
