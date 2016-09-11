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

USING_NS_CC;

void GameManager::runScene() {
    GameManagerBase::runScene();
    
    _scene->onTouchEnded = CC_CALLBACK_2(GameManager::onTouchEnded, this);
    
    _tileController = std::make_shared<TileController>(_scene);
    _tileController->onTaskRegistered = CC_CALLBACK_0(GameManager::onTileAnimationBegan, this);
    _tileController->onAllTaskFinished = CC_CALLBACK_0(GameManager::onTileAnimationEnded, this);
    
    _gameLogic = libspiral::make_unique<GameLogic>(_tileController);
    spawnTile();
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
}