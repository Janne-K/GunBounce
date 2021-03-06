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
    const float PLAYERPHYSSHOOTFORCE = 6000.0f;
    const float PLAYERROTATIONRATE = 450.0f;
    const float PLAYERVELOCITYLIMIT = 800.0f;
    const float STARPHYSRADIUS = 75.0f;
    const float STARPHYSMASS = 0.000001f;
    const float SHOTPHYSRADIUS = 20.0f;
    const float SHOTPHYSMASS = 0.1f;
    const float SHOTVELOCITYLIMIT = 700.0f;
    const float SCOREPOINTINTERVAL = 0.2f;

    const int COLL_PLAYER = 0x01;
    const int COLL_SHOT = 0x02;
    const int COLL_STAR = 0x04;
    const int COLL_LEVEL = 0x08;
    const int START_MAX_SHOTS = 2;
    const int LEVEL_SCORE_THRESHOLD = 500;
    const int GAMELAYER_TAG = 1000;
    const int MENU_TAG = 1001;
    
    cocos2d::Vec2 calculateNormalVecFromAngle(const float angle) {
        float radAngle = angle / 180.0f * M_PI;
        return cocos2d::Vec2(std::cos(radAngle), std::sin(radAngle));
    }
}
