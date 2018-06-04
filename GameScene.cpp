#include "GameScene.h"
#include "GameLayer.h"

namespace gunbounce {
    cocos2d::Scene* GunBounceScene::createScene()
    {
        return GunBounceScene::create();
    }
    
    bool GunBounceScene::init() {
        if ( !Scene::init() )
        {
            return false;
        }

        if( !Scene::initWithPhysics() )
        {
            return false;
        }
        
        auto physWorld = this->getPhysicsWorld();
        //physWorld->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
        physWorld->setGravity(cocos2d::Vec2::ZERO);
        
        auto layer = GunBounceLayer::create();
        this->addChild(layer);
        
        return true;
    }
}
