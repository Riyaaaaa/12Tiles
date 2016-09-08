//
//  GameManager.cpp
//  12Tiles
//
//  Created by Riya.Liel on 2016/09/08.
//
//

#include "GameManager.hpp"

USING_NS_CC;

void GameManager::runScene() {
    running_scene = GameScene::create();
    
    Director::getInstance()->runWithScene(running_scene);
}

void GameManager::update(float delta) {
    
}