#include "PlayerGun.h"
#include "ShotProjectile.h"
#include "GunBounceUtils.h"

namespace gunbounce {
    PlayerGun::PlayerGun(const float x, const float y, const float pmass, const float pradius, const float rrate, cocos2d::Scene* scene)
            : PHYSMASS(pmass), PHYSRADIUS(pradius), ROTATIONRATE(rrate) {
        this->gunSprite = cocos2d::Sprite::create("playergun.png");
        scene->addChild(this->gunSprite, 0);
        this->gunSprite->setPosition(x, y);
        
        auto gunPhysBody = cocos2d::PhysicsBody::createCircle(PHYSRADIUS,
                                cocos2d::PhysicsMaterial(1.0f, 1.0f, 0.0f));
        gunPhysBody->setMass(PHYSMASS);
        gunPhysBody->setCategoryBitmask(COLL_PLAYER);
        gunPhysBody->setCollisionBitmask(COLL_SHOT);
        gunPhysBody->setContactTestBitmask(0xFFFFFFFF);
        gunPhysBody->setVelocityLimit(PLAYERVELOCITYLIMIT);
        
        auto mass = gunPhysBody->getMass();
        cocos2d::log("Mass: %f", mass);
        this->gunSprite->addComponent(gunPhysBody);
        
        auto rotateBy = cocos2d::RotateBy::create(1, ROTATIONRATE);
        auto infiniteRotation = cocos2d::RepeatForever::create(rotateBy);
        this->gunSprite->runAction(infiniteRotation);
        
        auto category = gunPhysBody->getCategoryBitmask();
        auto collision =  gunPhysBody->getCollisionBitmask();
        cocos2d::log("Category %d, Collision %d", category, collision);
    }
    
    bool PlayerGun::canShoot() {
        // Check if we can shoot right now
        
        return true;
    }

    cocos2d::Sprite* PlayerGun::getSprite() {
        return this->gunSprite;
    }
}
