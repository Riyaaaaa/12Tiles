//
//  GameLogic.cpp
//  12Tiles
//
//  Created by Riya.Liel on 2016/09/10.
//
//

#include "GameLogic.hpp"

#include "SpiralLibrary/Structure/Index.hpp"
#include "Constants.h"

GameLogic::GameLogic(const std::shared_ptr<TileController>& controller) :
_tileController(controller) {
    
}

bool GameLogic::isTileMovable() {
    for(auto && index : Constants::TILE_RANGE) {
        for(auto && neighbor : CLOCKWISE_4_FOR) {
            
        }
    }
    return true;
}

void GameLogic::selectTile(libspiral::Index index) {
    auto& tiles = _tileController->getTiles();
    if(_selectedTile) {
        if(!tiles[index]) {
            
        }
        else if(_selectedTile->getValue() == tiles[index]->getValue()) {
            
        }
    }
    else {
        _selectedTile = tiles[index];
    }
}