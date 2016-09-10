//
//  TileController.cpp
//  12Tiles
//
//  Created by Riya.Liel on 2016/09/08.
//
//

#include "TileController.hpp"

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
        if(_tiles[index]->getBoundingBox().containsPoint(touchPos)) {
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