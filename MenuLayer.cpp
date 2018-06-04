#include "MenuLayer.h"
#include "GunBounceUtils.h"
#include "SimpleAudioEngine.h"

namespace gunbounce {
    bool MenuLayer::init() {
        this->setTag(MENU_TAG);

        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

        auto pauseLabel = cocos2d::Label::createWithTTF("PAUSED", "fonts/Marker Felt.ttf", 72);
        pauseLabel->setPosition(cocos2d::Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height / 2 + pauseLabel->getContentSize().height + 100.0f));
        this->addChild(pauseLabel, 1);
        
        auto creditLabel = cocos2d::Label::createWithTTF("BGM:\"Tech Live\" Kevin MacLeod (incompetech.com) - \
Licensed under Creative Commons: By Attribution 3.0 License: http://creativecommons.org/licenses/by/3.0/", "fonts/Marker Felt.ttf", 24);
        creditLabel->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
        creditLabel->setPosition(cocos2d::Vec2(origin.x, origin.y));
        this->addChild(creditLabel, 1);


        auto menu = cocos2d::Menu::create();

        auto resumeItem = cocos2d::MenuItemImage::create("menu_resume_1.png", "menu_resume_2.png",
                                                         CC_CALLBACK_1(MenuLayer::returnToGameCallback, this));
        resumeItem->setScale(2.0f);
        const auto resumeItemX = visibleSize.width / 2 - 200.0f;
        const auto resumeItemY = visibleSize.height / 2 - resumeItem->getContentSize().height;
        resumeItem->setPosition(cocos2d::Vec2(resumeItemX,resumeItemY));
        menu->addChild(resumeItem);

        auto closeItem = cocos2d::MenuItemImage::create("menu_exit_1.png", "menu_exit_2.png",
                                                        CC_CALLBACK_1(MenuLayer::menuCloseCallback, this));
        closeItem->setScale(2.0f);
        const auto closeItemX = visibleSize.width / 2 + 200.0f;
        const auto closeItemY = visibleSize.height / 2 - closeItem->getContentSize().height;
        closeItem->setPosition(cocos2d::Vec2(closeItemX,closeItemY));
        menu->addChild(closeItem);

        menu->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(menu, 1);


        return true;
    }
    
    void MenuLayer::menuCloseCallback(cocos2d::Ref* pSender)
    {
        cocos2d::Director::getInstance()->end();
    }
    
    void MenuLayer::returnToGameCallback(cocos2d::Ref* pSender) {
        // This probably should be handled by the resuming layer, instead of the menu
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
