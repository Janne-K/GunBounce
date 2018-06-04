#include "GameScene.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"

namespace gunbounce {
    cocos2d::Scene* GunBounceScene::createScene()
    {
        return GunBounceScene::create();
    }
    
    bool GunBounceScene::init() {
        if (!Scene::init())
            return false;
        
        if(!Scene::initWithPhysics())
            return false;
        
        auto physWorld = this->getPhysicsWorld();
        physWorld->setGravity(cocos2d::Vec2::ZERO);

        auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
        audio->preloadBackgroundMusic("techlive.mp3");
        audio->preloadEffect("bounce.ogg");
        audio->preloadEffect("collect.ogg");
        audio->preloadEffect("explosion.ogg");
        audio->preloadEffect("levelup.ogg");
        audio->preloadEffect("shoot.ogg");

        auto layer = GunBounceLayer::create();
        this->addChild(layer);
        audio->playBackgroundMusic("techlive.mp3", true);

        return true;
    }
}
