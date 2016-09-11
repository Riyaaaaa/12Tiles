//
//  TileController.cpp
//  12Tiles
//
//  Created by Riya.Liel on 2016/09/08.
//
//

#include "TileController.hpp"

#include "GameLogic.hpp"
#include "SpiralLibrary/Structure/MultiIndex.hpp"

using namespace Constants::TileLayout;
using namespace libspiral;
USING_NS_CC;

TileController::TileController(GameScene* scene) :
_scene(scene) {
    initTiles();
}

void TileController::initTiles() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    /* rendering tile background sprites */
    RenderTexture* tex = RenderTexture::create(visibleSize.width, visibleSize.height);
    _scene->addChild(tex);
    tex->setPosition(visibleSize / 2.0f);

    tex->begin();
    
    for(auto && index : Constants::TILE_RANGE) {
        auto tileBg = Sprite::create();
        tileBg->setTextureRect(cocos2d::Rect(0, 0, TILE_SIZE, TILE_SIZE));
        tileBg->setPosition(convertToPositionWithIndex(index));
        tileBg->setColor(Color3B::BLACK);
        tileBg->visit();
    }

    tex->end();
    
    /* init tiles array */
    for(auto && index : Constants::TILE_RANGE) {
        _tiles[index] = nullptr;
    }
}

void TileController::addTile(libspiral::Index index, int value) {
    if(!_tiles[index]) {
        auto tile = NumTile::create(value);
        _scene->addChild(tile);
        tile->setPosition(convertToPositionWithIndex(index));
        
        _tiles[index] = tile;
    }
}

void TileController::setTileValue(libspiral::Index index, int value) {
    _tiles[index]->setValue(value);
}

libspiral::Optional<libspiral::Index> TileController::hitTest(Vec2 touchPos) {
    libspiral::Optional<libspiral::Index> op;
    for(auto && index : Constants::TILE_RANGE) {
        if(_tiles[index] && _tiles[index]->getBoundingBox().containsPoint(touchPos)) {
            op = index;
            break;
        }
    }
    
    return op;
}

cocos2d::Vec2 TileController::convertToPositionWithIndex(libspiral::Index index) {
    Vec2 pos;
    pos.x = PADDING_X + index.x * (TILE_SIZE + MARGIN_X) + TILE_SIZE / 2.0f;
    pos.y = PADDING_Y + index.y * (TILE_SIZE + MARGIN_Y) + TILE_SIZE / 2.0f;
    
    return pos;
}

libspiral::Index TileController::convertToIndexWithPosition(cocos2d::Vec2 pos) {
    libspiral::Index index;
    
    index.x = roundf((pos.x - PADDING_X - TILE_SIZE / 2.0f) / (TILE_SIZE + MARGIN_X));
    index.y = roundf((pos.y - PADDING_Y - TILE_SIZE / 2.0f) / (TILE_SIZE + MARGIN_Y));
    
    return index;
}

void TileController::move(const std::vector<libspiral::Index>& path, libspiral::Index begin) {
    
    if(path.empty()) {
        //awake;
        return;
    }
    
    MoveTask task;
    task.tile = _tiles[begin];
    task.current = begin;
    task.path = path;
    task.elapsedTime = 0.0f;
    _moveTasks.push_back(task);

    _tiles[begin] = nullptr;
    
    if(onTaskRegistered) {
        onTaskRegistered();
    }
}

void TileController::update(float delta) {
    for(auto && task : _moveTasks) {
        auto start = convertToPositionWithIndex(task.current);
        auto target = convertToPositionWithIndex(task.path.back());
        task.elapsedTime += delta;
        if(task.elapsedTime >= Constants::MOVE_DURATION) {
            task.tile->setPosition(target);
            task.current = task.path.back();
            task.path.pop_back();
            task.elapsedTime = 0.0f;
        }
        else {
            task.tile->setPosition(start + (target - start) * (task.elapsedTime / Constants::MOVE_DURATION));
        }
    }
    
    auto it = std::remove_if(_moveTasks.begin(), _moveTasks.end(), [](const MoveTask& task){
        return task.path.empty();
    });
    
    
    if(it != _moveTasks.end()) {
        _moveTasks.erase(it, _moveTasks.end());
        
        if(_moveTasks.empty()) {
            if(onAllTaskFinished) {
                onAllTaskFinished();
            }
        }
    }
}