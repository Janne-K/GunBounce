#include "ShotProjectile.h"
#include "GunBounceUtils.h"

namespace gunbounce {
    ShotProjectile::ShotProjectile(const float x, const float y, const float angle, const float mass, const float force, const float ltime, cocos2d::Scene* const parentScene)
            : PHYSMASS(mass), PHYSRADIUS(30.0f), lifetime(ltime) {
        this->shotSprite = cocos2d::Sprite::create("shotprojectile.png");
        parentScene->addChild(this->shotSprite, 0);
        this->shotSprite->setPosition(x, y);
        this->shotSprite->setRotation(angle);
        
        auto shotPhysBody = cocos2d::PhysicsBody::createCircle(PHYSRADIUS,
                                cocos2d::PhysicsMaterial(1.0f, 1.0f, 0.0f));
        shotPhysBody->setMass(PHYSMASS);
        shotPhysBody->setCategoryBitmask(COLL_SHOT);
        shotPhysBody->setCollisionBitmask(COLL_PLAYER | COLL_SHOT);
        shotPhysBody->setContactTestBitmask(COLL_PLAYER);
        this->shotSprite->addComponent(shotPhysBody);
        shotPhysBody->applyForce(cocos2d::Vec2(force, 0.0f));
    }
    
    float ShotProjectile::getLifeTime() {
        return lifetime;
    }
    
    void ShotProjectile::decreaseLifeTime(float amount) {
        lifetime -= amount;
    }
    
    cocos2d::Sprite* ShotProjectile::getSprite() {
        return this->shotSprite;
    }
}
