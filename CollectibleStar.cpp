#include "CollectibleStar.h"
#include "GunBounceUtils.h"

namespace gunbounce {
    CollectibleStar::CollectibleStar(const float x, const float y, cocos2d::Layer* parentLayer) {
        this->starSprite = cocos2d::Sprite::create("collectiblestar.png");
        parentLayer->addChild(this->starSprite);
        this->starSprite->setPosition(x, y);
        this->starSprite->setTag(COLL_STAR);
        
        auto starPhysBody = cocos2d::PhysicsBody::createCircle(STARPHYSRADIUS,
                                cocos2d::PhysicsMaterial(1.0f, 1.0f, 0.0f));
        starPhysBody->setMass(STARPHYSMASS);
        starPhysBody->setCategoryBitmask(COLL_STAR);
        starPhysBody->setCollisionBitmask(COLL_PLAYER);
        starPhysBody->setContactTestBitmask(0xFFFFFFFF);
        starPhysBody->setVelocityLimit(0.0f);
        this->starSprite->addComponent(starPhysBody);
        
        auto rotateBy = cocos2d::RotateBy::create(1, -PLAYERROTATIONRATE / 2);
        auto infiniteRotation = cocos2d::RepeatForever::create(rotateBy);
        this->starSprite->runAction(infiniteRotation);
    }
    
    void CollectibleStar::setNewPosition(const float x, const float y) {
        this->starSprite->setPosition(x, y);
    }

    cocos2d::Sprite* CollectibleStar::getSprite() {
        return this->starSprite;
    }
}
