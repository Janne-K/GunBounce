#include <memory>
#include "GameLayer.h"
#include "MenuLayer.h"
#include "SimpleAudioEngine.h"

namespace gunbounce {
/*
    cocos2d::Scene* GunBounceLayer::createScene()
    {
        auto scene = cocos2d::Scene::create();
        auto layer = GunBounceLayer::create();

        scene->addChild(layer);
        return scene;
    }
*/
    // Print useful error message instead of segfaulting when files are not there.
    static void problemLoading(const char* filename)
    {
        printf("Error while loading: %s\n", filename);
        printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
    }

    // on "init" you need to initialize your instance
    bool GunBounceLayer::init()
    {
        this->setTag(GAMELAYER_TAG);
        
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

        auto edgeNode = cocos2d::Node::create();
        edgeNode->setTag(COLL_LEVEL);
        edgeNode->setPosition(cocos2d::Vec2(visibleSize.width/2, visibleSize.height/2));
        auto edge = cocos2d::PhysicsBody::createEdgeBox(visibleSize, cocos2d::PhysicsMaterial(1.0f, 1.0f, 0.0f));
        edge->setContactTestBitmask(0xFFFFFFFF);
        edgeNode->setPhysicsBody(edge);
        this->addChild(edgeNode);

        levelLabel = cocos2d::Label::createWithTTF("Level: 1", "fonts/Marker Felt.ttf", 48);
        scoreLabel = cocos2d::Label::createWithTTF("Score: 0", "fonts/Marker Felt.ttf", 48);
        if (levelLabel == nullptr || scoreLabel == nullptr)
        {
            problemLoading("'fonts/Marker Felt.ttf'");
        }
        else
        {
            levelLabel->setAnchorPoint(cocos2d::Vec2(1.0f, 0.5f));
            levelLabel->setPosition(cocos2d::Vec2(origin.x + visibleSize.width/2 - 100.0f,
                                    origin.y + visibleSize.height - levelLabel->getContentSize().height));
            scoreLabel->setPosition(cocos2d::Vec2(origin.x + visibleSize.width/2 + 100.0f,
                                    origin.y + visibleSize.height - scoreLabel->getContentSize().height));
            this->addChild(scoreLabel, 1);
            this->addChild(levelLabel, 1);
        }

        this->stageSetup();

        // Physics listener for player getting hit
        auto physicsListener = cocos2d::EventListenerPhysicsContact::create();
        physicsListener->onContactBegin = [this](cocos2d::PhysicsContact &contact) {

            //if (this->player == nullptr)
                //return true;

            auto nodeA = contact.getShapeA()->getBody()->getNode();
            auto nodeB = contact.getShapeB()->getBody()->getNode();
            if (nodeA && nodeB) {
                if (nodeA->getTag() == COLL_LEVEL || nodeB->getTag() == COLL_LEVEL || (nodeA->getTag() == COLL_SHOT && nodeB->getTag() == COLL_SHOT)) {
                    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
                    audio->playEffect("bounce.ogg", false, 1.0f, 1.0f, 1.0f);
                }
                else if ((nodeA->getTag() == COLL_SHOT && nodeB->getTag() == COLL_PLAYER) || (nodeA->getTag() == COLL_PLAYER && nodeB->getTag() == COLL_SHOT))
                    this->handlePlayerDeath();
                else if ((nodeA->getTag() == COLL_STAR && nodeB->getTag() == COLL_PLAYER) || (nodeA->getTag() == COLL_PLAYER && nodeB->getTag() == COLL_STAR))
                    this->handleCollectStar();
            }

            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(physicsListener, this);
        
        // Back button press listener
        auto backButtonListener = cocos2d::EventListenerKeyboard::create();
        backButtonListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
        {
            if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_BACK)
                this->spawnPauseMenu();
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(backButtonListener, this);

        // Player shoot input listener
        auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event){
            if (this->player == nullptr)
                this->stageSetup();
            else if (this->player->canShoot())
                this->playerShoot();
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

        return true;
    }

    void GunBounceLayer::addShotToList(std::shared_ptr<ShotProjectile> shotToAdd) {
        shots.push(shotToAdd);
    }
    
    void GunBounceLayer::stageSetup() {
        if (this->star == nullptr)
            this->createStar();

        this->score = 0;
        this->level = 1;
        this->updateLabels();
        
        this->maxShotsOnScreen = 0;
        this->checkMaxShots();
        this->maxShotsOnScreen = START_MAX_SHOTS;
        this->maxShotsIncreaseTimer = 0.0f;
        
        if (this->player == nullptr)
            this->createPlayer();
        
        this->randomizeStarPosition();
    }
    
    void GunBounceLayer::updateLabels() {
        if (this->levelLabel) {
            auto levelStr = "Level: " + std::to_string(this->level);
            this->levelLabel->setString(levelStr);
        }
        if (this->scoreLabel) {
            auto scoreStr = "Score: " + std::to_string(this->score);
            this->scoreLabel->setString(scoreStr);
        }
    }
    
    void GunBounceLayer::spawnPauseMenu() {
        this->pauseNodes();
        auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
        audio->pauseBackgroundMusic();
        
        auto scene = cocos2d::Director::getInstance()->getRunningScene();
        auto menuLayer = MenuLayer::create();
        scene->addChild(menuLayer, 10);
    }

    void GunBounceLayer::pauseNodes() {
        this->pause();
        for(const auto &child : this->getChildren())
        {
            child->pause();
        }
        this->getScene()->getPhysicsWorld()->setSpeed(0.0f);
    }

    void GunBounceLayer::handlePlayerDeath() {
        auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
        audio->playEffect("explosion.ogg", false, 1.0f, 1.0f, 1.0f);
        
        auto emitter = cocos2d::ParticleSun::create();
        emitter->setDuration(1.0f);
        emitter->setPosition(this->player->getSprite()->getPosition());
        emitter->setEmitterMode(cocos2d::ParticleSystem::Mode::RADIUS);
        emitter->setStartRadius(0.0f);
        emitter->setEndRadius(300.0f);
        this->addChild(emitter, 1);
        
        this->player->getSprite()->removeFromParentAndCleanup(true);
        player = nullptr;
    }
    
    void GunBounceLayer::handleCollectStar() {
        auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
        audio->playEffect("collect.ogg", false, 1.0f, 1.0f, 1.0f);
        
        auto emitter = cocos2d::ParticleFlower::create();
        emitter->setDuration(0.3f);
        emitter->setPosition(this->star->getSprite()->getPosition());
        emitter->setEmitterMode(cocos2d::ParticleSystem::Mode::RADIUS);
        emitter->setStartRadius(25.0f);
        emitter->setEndRadius(300.0f);
        this->addChild(emitter, 0);
        
        this->score += 100;
        if (this->score % LEVEL_SCORE_THRESHOLD == 0)
        {
            audio->playEffect("levelup.ogg", false, 1.0f, 1.0f, 1.0f);
            
            this->level++;
            this->maxShotsOnScreen = START_MAX_SHOTS + this->level - 1;

            auto levelUpEmitter = cocos2d::ParticleGalaxy::create();
            levelUpEmitter->setDuration(1.0f);
            levelUpEmitter->setEmitterMode(cocos2d::ParticleSystem::Mode::RADIUS);
            levelUpEmitter->setStartRadius(600.0f);
            levelUpEmitter->setEndRadius(100.0f);
            this->addChild(levelUpEmitter, 0);
        }
        
        this->updateLabels();
        
        this->randomizeStarPosition();
    }
    
    void GunBounceLayer::randomizeStarPosition() {
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        
        const auto padding = 5.0f;
        
        auto minX = STARPHYSRADIUS + padding;
        auto minY = STARPHYSRADIUS + padding;
        auto maxX = visibleSize.width - STARPHYSRADIUS - padding;
        auto maxY = visibleSize.height - STARPHYSRADIUS - padding;
        
        auto newX = cocos2d::RandomHelper::random_real(minX, maxX);
        auto newY = cocos2d::RandomHelper::random_real(minY, maxY);
        
        this->star->setNewPosition(newX, newY);
    }
    
    void GunBounceLayer::playerShoot() {
        auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
        audio->playEffect("shoot.ogg", false, 1.0f, 1.0f, 1.0f);
        
        auto position = player->getSprite()->getPosition();
        auto angle = player->getSprite()->getRotation();
        
        // cocos2d uses positive angle for clockwise rotation instead of counter-clockwise, so invert the angle
        auto offsetVec = calculateNormalVecFromAngle(-angle) * (PLAYERPHYSRADIUS + SHOTPHYSRADIUS + 30.0f);
        auto shotPosition = position + offsetVec;
        auto newShot = std::make_shared<ShotProjectile>(shotPosition.x, shotPosition.y, angle, PLAYERPHYSSHOOTFORCE, this);
        shots.push(newShot);

        auto particlePosition = position + (offsetVec * 0.75f);
        auto emitter = cocos2d::ParticleSun::create();
        emitter->setDuration(0.1f);
        emitter->setPosition(particlePosition);
        emitter->setEmitterMode(cocos2d::ParticleSystem::Mode::RADIUS);
        emitter->setStartRadius(0.0f);
        emitter->setEndRadius(75.0f);
        this->addChild(emitter, 0);

        auto gunPhysBody = player->getSprite()->getPhysicsBody();
        gunPhysBody->applyForce(cocos2d::Vec2(-PLAYERPHYSSHOOTFORCE, 0.0f));
        this->checkMaxShots();
    }
    
    void GunBounceLayer::checkMaxShots() {
        while (static_cast<int>(shots.size()) > maxShotsOnScreen)
            this->eraseOldestShot();
    }
    
    void GunBounceLayer::eraseOldestShot() {
        auto shotToErase = shots.front();
        auto sprite = shotToErase->getSprite();
        
        auto position = sprite->getPosition();
        auto emitter = cocos2d::ParticleSun::create();
        emitter->setDuration(0.1f);
        emitter->setPosition(position);
        this->addChild(emitter, 100);
        
        sprite->removeFromParentAndCleanup(true);
        shots.pop();
    }
    
    void GunBounceLayer::createPlayer() {
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
        player = std::make_shared<PlayerGun>(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y, this);
    }
    
    void GunBounceLayer::createStar() {
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
        star = std::make_shared<CollectibleStar>(visibleSize.width/2 + origin.x + 200.0f, visibleSize.height/2 + origin.y, this);
    }
}
