//
//  GameManager.cpp
//  12Tiles
//
//  Created by Riya.Liel on 2016/09/08.
//
//

#include "GameManager.hpp"
#include "Constants.h"

#include "SpiralLibrary/Random/Random.hpp"
#include "SpiralLibrary/Memory/MemoryUtils.hpp"
#include "SpiralLibrary/Cocos2d/ModalLayer.hpp"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

void GameManager::runScene() {
    GameManagerBase::runScene();
    
    _scene->onTouchEnded = CC_CALLBACK_2(GameManager::onTouchEnded, this);
    _scene->getPauseButton()->addClickEventListener(CC_CALLBACK_1(GameManager::pause, this));
    
    _tileController = std::make_shared<TileController>(_scene);
    _tileController->onTaskRegistered = CC_CALLBACK_0(GameManager::onTileAnimationBegan, this);
    _tileController->onAllTaskFinished = CC_CALLBACK_0(GameManager::onTileAnimationEnded, this);
    
    _gameLogic = libspiral::make_unique<GameLogic>(_tileController);
    _gameLogic->onSelectInvalidTile = [=](){
        _scene->awake();
    };
    
    spawnTile(); spawnTile();

}

void GameManager::update(float delta) {
    _tileController->update(delta);
}

void GameManager::spawnTile() {
    const auto& tiles = _tileController->getTiles();
    std::vector<libspiral::Index> emptyTileIndex;
    
    for(auto && index : Constants::TILE_RANGE) {
        if(!tiles[index]) {
            emptyTileIndex.push_back(index);
        }
    }
    
    std::size_t i = libspiral::Random<>::getValue(0ul, emptyTileIndex.size() - 1);
    int value = libspiral::Random<>::getValue(1, 3);
    
    _tileController->addTile(emptyTileIndex[i], value);
}

void GameManager::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* e) {
    auto op = _tileController->hitTest(touch->getLocation());
    if(op) {
        _gameLogic->selectTile(op.value());
    }
    else {
        auto index = _tileController->convertToIndexWithPosition(touch->getLocation());
        if(GameLogic::isVaildIndex(index)) {
            _gameLogic->selectTile(index);
        }
    }
}

void GameManager::onTileAnimationBegan() {
    _scene->getTouchListener()->setEnabled(false);
}

void GameManager::onTileAnimationEnded() {
    spawnTile();
    _scene->getTouchListener()->setEnabled(true);
    checkGameState();
}

void GameManager::checkGameState() {
    if(_gameLogic->isCleared()) {
        clear();
    }
    if(!_gameLogic->isTileMovable()) {
        gameover();
    }
}

void GameManager::pause(cocos2d::Ref* unused) {
    auto rootNode = CSLoader::createNode(Constants::FilePath::PAUSE_CSB);
    openModalWindow(rootNode);
}

void GameManager::gameover() {
    auto rootNode = CSLoader::createNode(Constants::FilePath::GAMEOVER_CSB);
    openModalWindow(rootNode);
}

void GameManager::clear() {
    auto rootNode = CSLoader::createNode(Constants::FilePath::CLEAR_CSB);
    openModalWindow(rootNode);
}

void GameManager::retry() {
    _gameLogic->purge();
    _tileController->reset();
    spawnTile(); spawnTile();
}

void GameManager::openModalWindow(cocos2d::Node* rootNode) {
    auto size = Director::getInstance()->getVisibleSize();
    libspiral::ModalLayer* layer = libspiral::ModalLayer::create();
    _scene->addChild(layer);
    layer->addChild(rootNode);
    
    rootNode->getChildByName<ui::Button*>(Constants::NodeName::RETRY_BUTTON)->addClickEventListener([=](Ref*) {
        retry();
        layer->removeFromParent();
    });
    
    rootNode->getChildByName<ui::Button*>(Constants::NodeName::END_BUTTON)->addClickEventListener([](Ref*) {
        Director::getInstance()->end();
        exit(0);
    });
    
    layer->setPosition(Vec2::ZERO);
    rootNode->setPosition(size / 2.0f);

}