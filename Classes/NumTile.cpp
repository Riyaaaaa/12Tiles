//
//  Tile.cpp
//  12Tiles
//
//  Created by Riya.Liel on 2016/09/10.
//
//

#include "NumTile.hpp"

#include "Constants.h"

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

void NumTile::addValue(int value) {
    setValue(_value + value);
}

void NumTile::setValue(int value) {
    _value = value;
    _tile->setColor(cocos2d::Color3B(255 * value / Constants::MAX_VALUE, 0 , 0));
    _numLabel->setString(cocos2d::StringUtils::format("%d", value));
}

bool NumTile::init(int value /* = 0 */) {
    if(!cocos2d::Node::init()) {
        return false;
    }
    
    _lightMask = cocos2d::Sprite::create();
    _lightMask->setTextureRect(cocos2d::Rect(0, 0,
                                              Constants::TileLayout::TILE_SIZE + 5,
                                              Constants::TileLayout::TILE_SIZE + 5));
    _lightMask->setColor(cocos2d::Color3B::WHITE);
    
    _tile = cocos2d::Sprite::create();
    _tile->setTextureRect(cocos2d::Rect(0, 0,
                                 Constants::TileLayout::TILE_SIZE,
                                 Constants::TileLayout::TILE_SIZE));
    _numLabel = cocos2d::Label::create();
    _numLabel->setSystemFontSize(60.0f);
    
    addChild(_lightMask);
    addChild(_tile);
    addChild(_numLabel);
    
    _lightMask->setVisible(false);
    _numLabel->setPosition(getContentSize() / 2.0f);
    
    setValue(value);
    
    setContentSize(cocos2d::Size(Constants::TileLayout::TILE_SIZE, Constants::TileLayout::TILE_SIZE));
    
    return true;
}

void NumTile::light(bool isLight) {
    _lightMask->setVisible(isLight);
}

bool NumTile::containsPoint(cocos2d::Vec2 pos) {
    auto size = Constants::TileLayout::TILE_SIZE / 2.0f;
    return cocos2d::Rect(getPosition().x - size, getPosition().y - size, size, size ).containsPoint(pos);
}

void NumTile::flip() {
    auto seq = cocos2d::Sequence::create(cocos2d::ScaleTo::create(Constants::FLIP_DURATION, 0, 1),
                                         cocos2d::ScaleTo::create(Constants::FLIP_DURATION, 1, 1), nullptr);
    _tile->runAction(seq);
}