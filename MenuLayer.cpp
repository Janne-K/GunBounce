#include "MenuLayer.h"
#include "GunBounceUtils.h"
#include "SimpleAudioEngine.h"

namespace gunbounce {
    static void problemLoading(const char* filename) {
        printf("Error while loading: %s\n", filename);
        printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
    }
    
    bool MenuLayer::init() {
        this->setTag(MENU_TAG);

        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

        auto pauseLabel = cocos2d::Label::createWithTTF("PAUSED", "fonts/Marker Felt.ttf", 72);
        auto creditLabel = cocos2d::Label::createWithTTF("BGM:\"Tech Live\" Kevin MacLeod (incompetech.com) - \
Licensed under Creative Commons: By Attribution 3.0 License: http://creativecommons.org/licenses/by/3.0/", "fonts/Marker Felt.ttf", 24);
        if (pauseLabel == nullptr || creditLabel == nullptr)
        {
            problemLoading("'fonts/Marker Felt.ttf'");
        }
        else
        {
            pauseLabel->setPosition(cocos2d::Vec2(origin.x + visibleSize.width/2,
                                    origin.y + visibleSize.height / 2 + pauseLabel->getContentSize().height + 100.0f));
            this->addChild(pauseLabel, 1);
            
            creditLabel->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
            creditLabel->setPosition(cocos2d::Vec2(origin.x, origin.y));
            this->addChild(creditLabel, 1);
        }

        auto resumeItem = cocos2d::MenuItemImage::create(
                                               "menu_resume_1.png",
                                               "menu_resume_2.png",
                                               CC_CALLBACK_1(MenuLayer::returnToGameCallback, this));
        if (resumeItem == nullptr ||
            resumeItem->getContentSize().width <= 0 ||
            resumeItem->getContentSize().height <= 0)
        {
            problemLoading("'menu_resume_1.png' and 'menu_resume_2.png'");
        }
        else
        {
            resumeItem->setScale(2.0f);
            float x = visibleSize.width / 2 - 200.0f;
            float y = visibleSize.height / 2 - resumeItem->getContentSize().height;
            resumeItem->setPosition(cocos2d::Vec2(x,y));
        }

        auto closeItem = cocos2d::MenuItemImage::create(
                                               "menu_exit_1.png",
                                               "menu_exit_2.png",
                                               CC_CALLBACK_1(MenuLayer::menuCloseCallback, this));
        if (closeItem == nullptr ||
            closeItem->getContentSize().width <= 0 ||
            closeItem->getContentSize().height <= 0)
        {
            problemLoading("'menu_exit_1.png' and 'menu_exit_2.png'");
        }
        else
        {
            closeItem->setScale(2.0f);
            float x = visibleSize.width / 2 + 200.0f;
            float y = visibleSize.height / 2 - closeItem->getContentSize().height;
            closeItem->setPosition(cocos2d::Vec2(x,y));
        }

        auto menu = cocos2d::Menu::create();
        menu->addChild(resumeItem);
        menu->addChild(closeItem);
        menu->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(menu, 1);

        return true;
    }
    
    void MenuLayer::menuCloseCallback(cocos2d::Ref* pSender)
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
    
    void MenuLayer::returnToGameCallback(cocos2d::Ref* pSender) {
        auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
        audio->resumeBackgroundMusic();
        
        auto gameLayer = this->getScene()->getChildByTag(GAMELAYER_TAG);
        gameLayer->resume();
        for(const auto &child : gameLayer->getChildren())
        {
            child->resume();
        }
        this->getScene()->getPhysicsWorld()->setSpeed(1.0f);
        this->removeFromParentAndCleanup(true);
    }
}
