#include "ShotProjectile.h"
#include "GunBounceUtils.h"

namespace gunbounce {
    ShotProjectile::ShotProjectile(const float x, const float y, const float angle, const float force, cocos2d::Layer* const parentLayer) {
        this->shotSprite = cocos2d::Sprite::create("shotprojectile.png");
        parentLayer->addChild(this->shotSprite);
        this->shotSprite->setPosition(x, y);
        this->shotSprite->setRotation(angle);
        this->shotSprite->setTag(COLL_SHOT);
        
        auto shotPhysBody = cocos2d::PhysicsBody::createCircle(SHOTPHYSRADIUS,
                                cocos2d::PhysicsMaterial(1.0f, 1.0f, 0.0f));
        shotPhysBody->setMass(SHOTPHYSMASS);
        shotPhysBody->setCategoryBitmask(COLL_SHOT);
        shotPhysBody->setCollisionBitmask(COLL_PLAYER | COLL_SHOT);
        shotPhysBody->setContactTestBitmask(0xFFFFFFFF);
        shotPhysBody->setVelocityLimit(SHOTVELOCITYLIMIT);
        this->shotSprite->addComponent(shotPhysBody);
        shotPhysBody->applyForce(cocos2d::Vec2(force, 0.0f));
    }

    cocos2d::Sprite* ShotProjectile::getSprite() {
        return this->shotSprite;
    }
}
