//
//  TileController.hpp
//  12Tiles
//
//  Created by Riya.Liel on 2016/09/08.
//
//

#ifndef TileController_hpp
#define TileController_hpp

#include "SpiralLibrary/Container/MultiArray.hpp"
#include "SpiralLibrary/Structure/Index.hpp"
#include "SpiralLibrary/Optional/Optional.hpp"

#include "Constants.h"
#include "cocos2d.h"
#include "GameScene.h"
#include "NumTile.hpp"

class TileController {
public:
    typedef libspiral::MultiArray<  NumTile*,
                                    Constants::TileLayout::NUMBER_OF_TILES_Y,
                                    Constants::TileLayout::NUMBER_OF_TILES_X>
            tile_arr_t;
    
public:
    TileController(GameScene* scene);
    void initTiles();
    
    bool isTileMovable();
    const tile_arr_t& getTiles() { return _tiles; };
    
    void addTile(libspiral::Index index, int value);
    void setTileValue(libspiral::Index index, int value);
    void setSelectedTile(libspiral::Index index) { _selectedTile = _tiles[index]; }
    
    libspiral::Optional<libspiral::Index> hitTest(cocos2d::Vec2 touchPos);
    
    static cocos2d::Vec2 convertToPositionWithIndex(libspiral::Index index);
    
private:
    tile_arr_t _tiles;
    NumTile* _selectedTile;
    
    GameScene* _scene;
    
};

#endif /* TileController_hpp */
