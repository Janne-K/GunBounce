#include <iostream>
#include "PlayerGun.h"
#include "GunBounceUtils.h"

namespace gunbounce {
    PlayerGun::PlayerGun(const double x, const double y, cocos2d::Scene* parentScene) {
        this->gunSprite = cocos2d::Sprite::create("playergun.png");
        parentScene->addChild(this->gunSprite, 0);
        this->gunSprite->setPosition(x, y);
        
        auto gunPhysBody = cocos2d::PhysicsBody::createCircle(100.0f,
                                cocos2d::PhysicsMaterial(0.1f, 1.0f, 0.0f));
        this->gunSprite->addComponent(gunPhysBody);
        
        auto rotateBy = cocos2d::RotateBy::create(1, 180.0f);
        auto infiniteRotation = cocos2d::RepeatForever::create(rotateBy);
        this->gunSprite->runAction(infiniteRotation);
    }
    
    void PlayerGun::tryToShoot() {
        //auto rotation = this->gunSprite->getRotation();
        //auto impulseVec = calculateNormalVecFromAngle(rotation);
        //impulseVec *= 100000.0f;
        
        auto gunPhysBody = this->gunSprite->getPhysicsBody();

        //gunPhysBody->applyImpulse(impulseVec);
        gunPhysBody->applyImpulse(cocos2d::Vec2(-1000000.0f, 0.0f));
        cocos2d::log("Shoot event");
    }
}
