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
#include "Structure.h"

class TileController {
public:
    typedef libspiral::MultiArray<  NumTile*,
                                    Constants::TileLayout::NUMBER_OF_TILES_Y,
                                    Constants::TileLayout::NUMBER_OF_TILES_X>
            tile_arr_t;
    
public:
    TileController(GameScene* scene);
    void initTiles();
    
    const tile_arr_t& getTiles() { return _tiles; };
    
    void addTile(libspiral::Index index, int value);
    void setTileValue(libspiral::Index index, int value);
    
    void move(const std::vector<libspiral::Index>& path, libspiral::Index begin);
    
    void update(float delta);
    
    std::function<void()> onTaskRegistered;
    std::function<void()> onAllTaskFinished;
    
    libspiral::Optional<libspiral::Index> hitTest(cocos2d::Vec2 touchPos);
    
    static cocos2d::Vec2 convertToPositionWithIndex(libspiral::Index index);
    static libspiral::Index convertToIndexWithPosition(cocos2d::Vec2 pos);
    
private:
    tile_arr_t _tiles;
    GameScene* _scene;
    std::vector<MoveTask> _moveTasks;
    
};

#endif /* TileController_hpp */
