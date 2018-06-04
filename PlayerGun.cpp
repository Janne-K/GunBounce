#include "PlayerGun.h"
#include "ShotProjectile.h"
#include "GunBounceUtils.h"

namespace gunbounce {
    PlayerGun::PlayerGun(const float x, const float y, cocos2d::Layer* parentLayer) {
        this->gunSprite = cocos2d::Sprite::create("playergun.png");
        parentLayer->addChild(this->gunSprite);
        this->gunSprite->setPosition(x, y);
        this->gunSprite->setTag(COLL_PLAYER);
        
        auto gunPhysBody = cocos2d::PhysicsBody::createCircle(PLAYERPHYSRADIUS,
                                cocos2d::PhysicsMaterial(1.0f, 1.0f, 0.0f));
        gunPhysBody->setMass(PLAYERPHYSMASS);
        gunPhysBody->setCategoryBitmask(COLL_PLAYER);
        gunPhysBody->setCollisionBitmask(COLL_SHOT | COLL_STAR);
        gunPhysBody->setContactTestBitmask(0xFFFFFFFF);
        gunPhysBody->setVelocityLimit(PLAYERVELOCITYLIMIT);
        this->gunSprite->addComponent(gunPhysBody);
        
        this->gunSprite->setRotation(-90.0f); // Make the gun point up at start
        auto rotateBy = cocos2d::RotateBy::create(1, PLAYERROTATIONRATE);
        auto infiniteRotation = cocos2d::RepeatForever::create(rotateBy);
        this->gunSprite->runAction(infiniteRotation);
    }
    
    bool PlayerGun::canShoot() {
        // Check if we can shoot right now
        return true;
    }

    cocos2d::Sprite* PlayerGun::getSprite() {
        return this->gunSprite;
    }
}
