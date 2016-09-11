//
//  GameLogic.cpp
//  12Tiles
//
//  Created by Riya.Liel on 2016/09/10.
//
//

#include "GameLogic.hpp"

#include "AstarSearch.hpp"
#include "SpiralLibrary/Structure/Index.hpp"
#include "Constants.h"

GameLogic::GameLogic(const std::shared_ptr<TileController>& controller) :
_tileController(controller),
_selectedTile(std::make_pair(libspiral::Index{}, nullptr)) {
    
}

bool GameLogic::isTileMovable() {
    auto& tiles = _tileController->getTiles();
    for(auto && index : Constants::TILE_RANGE) {
        for(auto && neighbor : CLOCKWISE_4_FOR) {
            if(isVaildIndex(index + neighbor) &&
               (!tiles[index + neighbor] ||
                tiles[index]->getValue() == tiles[index + neighbor]->getValue())) {
                   return true;
               }
        }
    }
    return false;
}

void GameLogic::selectTile(libspiral::Index index) {
    auto& tiles = _tileController->getTiles();
    if(_selectedTile.second) {
        if(_selectedTile.second != tiles[index] &&
           (!tiles[index] || (_selectedTile.second->getValue() == tiles[index]->getValue()))) {
            AStar aster(_selectedTile.first, index);
            _tileController->move(aster.search(tiles), _selectedTile.first);
        }
        else {
            //awake
        }
        purge();
    }
    else {
        _selectedTile.first = index;
        _selectedTile.second = tiles[index];
    }
}

bool GameLogic::isVaildIndex(libspiral::Index index) {
    if(index.x >= 0 && index.y >= 0 && index.x < Constants::TileLayout::NUMBER_OF_TILES_X && index.y < Constants::TileLayout::NUMBER_OF_TILES_Y) {
        return true;
    }
    return false;
}

void GameLogic::purge() {
    _selectedTile = std::make_pair(libspiral::Index{}, nullptr);
}