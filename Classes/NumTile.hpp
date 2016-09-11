//
//  Tile.hpp
//  12Tiles
//
//  Created by Riya.Liel on 2016/09/10.
//
//

#ifndef Tile_hpp
#define Tile_hpp

#include "cocos2d.h"

class NumTile : public cocos2d::Node {
public:
    static NumTile* create(int value = 0);
    bool init(int value = 0);
    
    void addValue(int value);
    void setValue(int value);
    
    void light(bool isLight);
    void flip();
    
    bool containsPoint(cocos2d::Vec2 pos);
    
    CC_SYNTHESIZE_READONLY(int, _value, Value);
    
private:
    cocos2d::Label* _numLabel;
    cocos2d::Sprite* _tile;
    cocos2d::Sprite* _lightMask;
};

#endif /* Tile_hpp */
