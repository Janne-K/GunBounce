#include <cmath>
#include "cocos2d.h"
#include "GunBounceUtils.h"

namespace gunbounce {
    
    const cocos2d::Size DESIGN_RESOLUTION_SIZE = cocos2d::Size(1920, 1080);
    const cocos2d::Size SMALL_RESOLUTION_SIZE = cocos2d::Size(960, 540);
    const cocos2d::Size MEDIUM_RESOLUTION_SIZE = cocos2d::Size(1920, 1080);
    const cocos2d::Size LARGE_RESOLUTION_SIZE = cocos2d::Size(3840, 2160);

    const float PLAYERPHYSRADIUS = 60.0f;
    const float PLAYERPHYSMASS = 0.1f;
    const float PLAYERPHYSSHOOTFORCE = 5000.0f;
    const float PLAYERROTATIONRATE = 360.0f;
    const float PLAYERVELOCITYLIMIT = 1200.0f;
    const float STARPHYSRADIUS = 75.0f;
    const float SHOTPHYSRADIUS = 30.0f;
    const float SHOTLIFETIME = 3.0f;
    const float INCREASE_MAX_SHOTS_INTERVAL = 10.0f;

    const int COLL_PLAYER = 0x01;
    const int COLL_SHOT = 0x02;
    const int COLL_STAR = 0x04;
    const int START_MAX_SHOTS = 2;
    const int LEVEL_SCORE_THRESHOLD = 500;
    
    cocos2d::Vec2 calculateNormalVecFromAngle(const float angle) {
        float radAngle = angle / 180.0f * M_PI;
        return cocos2d::Vec2(std::cos(radAngle), std::sin(radAngle));
    }
}
