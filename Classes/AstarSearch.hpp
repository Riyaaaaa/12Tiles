//
//  AstarSearch.hpp
//  12Tiles
//
//  Created by Riya.Liel on 2016/09/11.
//
//

#ifndef AstarSearch_hpp
#define AstarSearch_hpp

#include "SpiralLibrary/Algorithm/AStar.hpp"
#include "SpiralLibrary/Container/MultiArray.hpp"
#include "Constants.h"
#include "NumTile.hpp"

typedef libspiral::MultiArray<  NumTile*,
Constants::TileLayout::NUMBER_OF_TILES_Y,
Constants::TileLayout::NUMBER_OF_TILES_X> map_t;

struct TileRater : libspiral::IRater<TileRater, map_t> {
    int heuristics(const map_t& map, libspiral::Index index, libspiral::Index end);
    std::vector<libspiral::Index> getIndexes(const map_t& map, libspiral::Index index, libspiral::Index end);
};

typedef libspiral::AStar<TileRater> AStar;

#endif /* AstarSearch_hpp */
