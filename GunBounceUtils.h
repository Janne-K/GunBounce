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
    extern const float STARPHYSRADIUS;
    extern const float SHOTPHYSRADIUS;
    extern const float SHOTLIFETIME;
    extern const float INCREASE_MAX_SHOTS_INTERVAL;
    
    extern const int COLL_PLAYER;
    extern const int COLL_SHOT;
    extern const int COLL_STAR;
    extern const int START_MAX_SHOTS;
    extern const int LEVEL_SCORE_THRESHOLD;
    extern const int GAMELAYER_TAG;
    extern const int MENU_TAG;

    cocos2d::Vec2 calculateNormalVecFromAngle(const float angle);
}
    
#endif // __GUNBOUNCE_UTILS_H__
