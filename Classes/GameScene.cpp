#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "SpiralLibrary/Function/MaybeCall.hpp"

USING_NS_CC;

using namespace cocostudio::timeline;

GameScene* GameScene::createScene() {
    GameScene *pRet = new(std::nothrow) GameScene();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }
    else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

    rootNode->getChildByName<Sprite*>("Bg")
        ->setPosition(Director::getInstance()->getWinSize() / 2.0f);
    
    initLisener();
    
    return true;
}

void GameScene::initLisener() {
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* e) {
        libspiral::Optional<bool> op = libspiral::maybeCall(onTouchBegan, touch, e);
        if(op) {
            return op.value();
        }
        return true;
    };
    
    _touchListener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* e) {
        libspiral::maybeCall(onTouchMoved, touch, e);
    };
    
    _touchListener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* e) {
        libspiral::maybeCall(onTouchEnded, touch, e);
    };
    
    _touchListener->onTouchCancelled = [=](cocos2d::Touch* touch, cocos2d::Event* e) {
        libspiral::maybeCall(onTouchCancelled, touch, e);
    };
    
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);
}


