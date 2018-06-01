#include <memory>
#include <iostream>
#include "GameScene.h"
//#include "SimpleAudioEngine.h"

namespace gunbounce {
        
    cocos2d::Scene* GunBounce::createScene()
    {
        return GunBounce::create();
    }

    // Print useful error message instead of segfaulting when files are not there.
    static void problemLoading(const char* filename)
    {
        printf("Error while loading: %s\n", filename);
        printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
    }

    // on "init" you need to initialize your instance
    bool GunBounce::init()
    {
        //////////////////////////////
        // 1. super init first
        if ( !Scene::init() )
        {
            return false;
        }

        if( !Scene::initWithPhysics() )
        {
            return false;
        }

        auto physWorld = this->getPhysicsWorld();
        physWorld->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
        physWorld->setGravity(cocos2d::Vec2::ZERO);

        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

        /////////////////////////////
        // 2. add a menu item with "X" image, which is clicked to quit the program
        //    you may modify it.

        // add a "close" icon to exit the progress. it's an autorelease object
        auto closeItem = cocos2d::MenuItemImage::create(
                                               "CloseNormal.png",
                                               "CloseSelected.png",
                                               CC_CALLBACK_1(GunBounce::menuCloseCallback, this));

        if (closeItem == nullptr ||
            closeItem->getContentSize().width <= 0 ||
            closeItem->getContentSize().height <= 0)
        {
            problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
        }
        else
        {
            float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
            float y = origin.y + closeItem->getContentSize().height/2;
            closeItem->setPosition(cocos2d::Vec2(x,y));
        }

        // create menu, it's an autorelease object
        auto menu = cocos2d::Menu::create(closeItem, NULL);
        menu->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(menu, 1);

        /////////////////////////////
        // 3. add your codes below...

        // add a label shows "Hello World"
        // create and initialize a label

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

        player = std::make_shared<PlayerGun>(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y, this);
        
        auto edge = cocos2d::PhysicsBody::createEdgeBox(visibleSize, cocos2d::PhysicsMaterial(1.0f, 1.0f, 0.0f));
        auto edgeNode = cocos2d::Node::create();
        edgeNode->setPosition(cocos2d::Vec2(visibleSize.width/2, visibleSize.height/2));
        edgeNode->setPhysicsBody(edge);
        this->addChild(edgeNode);

        touchListener = cocos2d::EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event){
            this->player->tryToShoot();
            return true;
        };
        _eventDispatcher->addEventListenerWithFixedPriority(this->touchListener, 1);
        return true;
    }


    void GunBounce::menuCloseCallback(Ref* pSender)
    {
        //Close the cocos2d-x game scene and quit the application
        cocos2d::Director::getInstance()->end();

        #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif

        /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

        //EventCustom customEndEvent("game_scene_close_event");
        //_eventDispatcher->dispatchEvent(&customEndEvent);


    }
    
    void GunBounce::addShotToList(std::shared_ptr<ShotProjectile> shotToAdd) {
        shots.push_back(shotToAdd);
    }
}
