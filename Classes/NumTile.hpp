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

class NumTile : public cocos2d::Sprite {
public:
    NumTile();
    static NumTile* create(int value = 0);
    bool init(int value = 0);
    
    void setValue(int value);
    
    CC_SYNTHESIZE_READONLY(int, _value, Value);
    
private:
    cocos2d::Label* _numLabel;
};

#endif /* Tile_hpp */
