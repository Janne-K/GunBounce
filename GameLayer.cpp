#include <memory>
#include "GameLayer.h"
#include "MenuLayer.h"
//#include "SimpleAudioEngine.h"

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

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.

        // add a "close" icon to exit the progress. it's an autorelease object


        /////////////////////////////
        // 3. add your codes below...

        // add a label shows "Hello World"
        // create and initialize a label
/*
        auto label = cocos2d::Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
        if (label == nullptr)
        {
            problemLoading("'fonts/Marker Felt.ttf'");
        }
        else
        {
            // position the label on the center of the screen
            label->setPosition(cocos2d::Vec2(origin.x + visibleSize.width/2,
                                    origin.y + visibleSize.height - label->getContentSize().height));

            // add the label as a child to this layer
            this->addChild(label, 1);
        }
*/
        auto edge = cocos2d::PhysicsBody::createEdgeBox(visibleSize, cocos2d::PhysicsMaterial(1.0f, 1.0f, 0.0f));
        auto edgeNode = cocos2d::Node::create();
        edgeNode->setPosition(cocos2d::Vec2(visibleSize.width/2, visibleSize.height/2));
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

        this->createStar();
        
        this->stageSetup();

        auto shotHitListener = cocos2d::EventListenerPhysicsContact::create();
        shotHitListener->onContactBegin = [this](cocos2d::PhysicsContact &contact) {
            if (this->player == nullptr)
                return true;

            auto nodeA = contact.getShapeA()->getBody()->getNode();
            auto nodeB = contact.getShapeB()->getBody()->getNode();
            if (nodeA && nodeB) {
                if (nodeA->getTag() == COLL_SHOT  || nodeB->getTag() == COLL_SHOT)
                    this->handlePlayerDeath();
                else if (nodeA->getTag() == COLL_STAR || nodeB->getTag() == COLL_STAR)
                    this->handleCollectStar();
            }

            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(shotHitListener, this);
        
        // android back press event
        auto backButtonListener = cocos2d::EventListenerKeyboard::create();
        backButtonListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
        {
            if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_BACK)
                this->spawnPauseMenu();
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(backButtonListener, this);

        auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event){
            if (this->player == nullptr)
                this->stageSetup();
            else if (this->player->canShoot())
                this->playerShoot();
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        
        
        this->scheduleUpdate();

        return true;
    }
    
    void GunBounceLayer::update(float dt) {
            return;
        /*
        this->maxShotsIncreaseTimer += dt;
        while (this->maxShotsIncreaseTimer >= INCREASE_MAX_SHOTS_INTERVAL) {
            this->maxShotsIncreaseTimer -= INCREASE_MAX_SHOTS_INTERVAL;
            this->maxShotsOnScreen++;
        }*/
        /*
        auto isDead = [](std::shared_ptr<ShotProjectile> shot) {
            return shot->getLifeTime() < 0.0f;
        };
        
        for (auto shot : shots) {
            shot->decreaseLifeTime(dt);
            if (isDead(shot)) {

                auto sprite = shot->getSprite();
                
                auto position = sprite->getPosition();
                auto emitter = cocos2d::ParticleSun::create();
                emitter->setDuration(0.1f);
                emitter->setPosition(position);
                this->addChild(emitter, 100);
                
                sprite->removeFromParentAndCleanup(true);
                
            }
        }
        
        shots.erase(std::remove_if(shots.begin(), shots.end(), isDead), shots.end());*/
    }

    void GunBounceLayer::addShotToList(std::shared_ptr<ShotProjectile> shotToAdd) {
        shots.push(shotToAdd);
    }
    
    void GunBounceLayer::stageSetup() {
        this->score = 0;
        this->level = 1;
        this->updateLabels();
        
        this->maxShotsOnScreen = 0;
        this->checkMaxShots();
        this->maxShotsOnScreen = START_MAX_SHOTS;
        this->maxShotsIncreaseTimer = 0.0f;
        
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
        //_actionManager->pauseTarget(this);
        //this->pauseRecursiveAllChildren();
        //this->pauseSchedulerAndActions();
        //this->player->getSprite()->pauseSchedulerAndActions();
        this->pauseNodes();
        
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

    void GunBounceLayer::resumeNodes() {
        this->resume();
        for(const auto &child : this->getChildren())
        {
            child->resume();
        }
        this->getScene()->getPhysicsWorld()->setSpeed(1.0f);
    }

    void GunBounceLayer::handlePlayerDeath() {
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
        auto position = player->getSprite()->getPosition();
        auto angle = player->getSprite()->getRotation();
        
        // cocos2d uses positive angle for clockwise rotation instead of counter-clockwise, so invert the angle
        auto offsetVec = calculateNormalVecFromAngle(-angle) * (PLAYERPHYSRADIUS + SHOTPHYSRADIUS + 30.0f);
        auto shotPosition = position + offsetVec;
        auto newShot = std::make_shared<ShotProjectile>(shotPosition.x, shotPosition.y, angle, PLAYERPHYSMASS, PLAYERPHYSSHOOTFORCE, SHOTLIFETIME, this);
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
        player = std::make_shared<PlayerGun>(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y,
                                             PLAYERPHYSMASS, PLAYERPHYSRADIUS, PLAYERROTATIONRATE, this);
    }
    
    void GunBounceLayer::createStar() {
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
        star = std::make_shared<CollectibleStar>(visibleSize.width/2 + origin.x + 200.0f, visibleSize.height/2 + origin.y, this);
    }
}
