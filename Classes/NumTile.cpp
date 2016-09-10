//
//  Tile.cpp
//  12Tiles
//
//  Created by Riya.Liel on 2016/09/10.
//
//

#include "NumTile.hpp"

#include "Constants.h"

NumTile::NumTile() {
    
}

NumTile* NumTile::create(int value /* = 0 */) {
    NumTile *pRet = new(std::nothrow) NumTile();
    if (pRet && pRet->init(value)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

void NumTile::setValue(int value) {
    _value = value;
    setColor(cocos2d::Color3B(256 * value / Constants::MAX_VALUE, 0 , 0));
    _numLabel->setString(cocos2d::StringUtils::format("%d", value));
}

bool NumTile::init(int value /* = 0 */) {
    if(!cocos2d::Sprite::init()) {
        return false;
    }
    
    setTextureRect(cocos2d::Rect(0, 0,
                                 Constants::TileLayout::TILE_SIZE,
                                 Constants::TileLayout::TILE_SIZE));
    _numLabel = cocos2d::Label::create();
    _numLabel->setSystemFontSize(60.0f);
    addChild(_numLabel);
    
    _numLabel->setPosition(getContentSize() / 2.0f);
    
    setValue(value);
    
    return true;
}