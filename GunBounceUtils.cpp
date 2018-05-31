#include <cmath>
#include "cocos2d.h"
#include "GunBounceUtils.h"

namespace gunbounce {
    
    const cocos2d::Size DESIGN_RESOLUTION_SIZE = cocos2d::Size(1920, 1080);
    const cocos2d::Size SMALL_RESOLUTION_SIZE = cocos2d::Size(960, 540);
    const cocos2d::Size MEDIUM_RESOLUTION_SIZE = cocos2d::Size(1920, 1080);
    const cocos2d::Size LARGE_RESOLUTION_SIZE = cocos2d::Size(3840, 2160);
    
    cocos2d::Vec2 calculateNormalVecFromAngle(const float angle) {
        float radAngle = angle / 180.0f * M_PI;
        return cocos2d::Vec2(std::cos(radAngle), std::sin(radAngle));
    }
}
