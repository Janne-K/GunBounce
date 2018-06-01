#include "PlayerGun.h"
#include "ShotProjectile.h"
#include "GunBounceUtils.h"

namespace gunbounce {
    PlayerGun::PlayerGun(const float x, const float y, cocos2d::Scene* scene)
            : PHYSMASS(0.1f), PHYSRADIUS(100.0f), PHYSSHOOTFORCE(3000.0f), ROTATIONRATE(180.0f), parentScene(scene) {
        this->gunSprite = cocos2d::Sprite::create("playergun.png");
        parentScene->addChild(this->gunSprite, 0);
        this->gunSprite->setPosition(x, y);
        
        auto gunPhysBody = cocos2d::PhysicsBody::createCircle(PHYSRADIUS,
                                cocos2d::PhysicsMaterial(1.0f, 1.0f, 0.0f));
        gunPhysBody->setMass(PHYSMASS);
        auto mass = gunPhysBody->getMass();
        cocos2d::log("Mass: %f", mass);
        this->gunSprite->addComponent(gunPhysBody);
        
        auto rotateBy = cocos2d::RotateBy::create(1, ROTATIONRATE);
        auto infiniteRotation = cocos2d::RepeatForever::create(rotateBy);
        this->gunSprite->runAction(infiniteRotation);
    }
    
    void PlayerGun::tryToShoot() {
        // Check if we can shoot right now
        
        this->shoot();
    }
    
    void PlayerGun::shoot() {
        auto position = this->gunSprite->getPosition();
        auto angle = this->gunSprite->getRotation();
        
        // cocos2d uses positive angle for clockwise rotation instead of counter-clockwise, so invert the angle
        auto offsetVec = calculateNormalVecFromAngle(-angle) * (PHYSRADIUS + 50.0f);
        position += offsetVec;
        
        auto newShot = std::make_shared<ShotProjectile>(position.x, position.y, angle, PHYSMASS, PHYSSHOOTFORCE, parentScene);
        
        auto gunPhysBody = this->gunSprite->getPhysicsBody();
        gunPhysBody->applyForce(cocos2d::Vec2(-PHYSSHOOTFORCE, 0.0f));
        cocos2d::log("angle: %f", angle);
    }
}
