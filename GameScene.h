#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

namespace gunbounce {
    class GunBounceScene : public cocos2d::Scene
    {
    public:
        static cocos2d::Scene* createScene();
        virtual bool init();
        CREATE_FUNC(GunBounceScene);
    };
}
#endif // __GAME_SCENE_H__
