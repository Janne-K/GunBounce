#include "ShotProjectile.h"
#include "GunBounceUtils.h"

namespace gunbounce {
    ShotProjectile::ShotProjectile(const float x, const float y, const float angle, const float mass, const float force, cocos2d::Scene* const parentScene)
            : PHYSMASS(mass), PHYSRADIUS(30.0f) {
        this->shotSprite = cocos2d::Sprite::create("shotprojectile.png");
        parentScene->addChild(this->shotSprite, 0);
        this->shotSprite->setPosition(x, y);
        this->shotSprite->setRotation(angle);
                
        auto shotPhysBody = cocos2d::PhysicsBody::createCircle(PHYSRADIUS,
                                cocos2d::PhysicsMaterial(1.0f, 1.0f, 0.0f));
        shotPhysBody->setMass(PHYSMASS);
        this->shotSprite->addComponent(shotPhysBody);
        shotPhysBody->applyForce(cocos2d::Vec2(force, 0.0f));
    }
}
