//
//  AstarSearch.cpp
//  12Tiles
//
//  Created by Riya.Liel on 2016/09/11.
//
//

#include "AstarSearch.hpp"
#include "GameLogic.hpp"

int TileRater::heuristics(const map_t& map, libspiral::Index index, libspiral::Index end) {
    return index.manhattanDistance(end);
}

std::vector<libspiral::Index> TileRater::getIndexes(const map_t& map, libspiral::Index index, libspiral::Index end) {
    std::vector<libspiral::Index> indexes;
    for(auto && neigbor : CLOCKWISE_4_FOR) {
        auto ix = index + neigbor;
        if(GameLogic::isVaildIndex(ix) && (!map[ix] || ix == end)) {
            indexes.push_back(ix);
        }
    }
    
    return indexes;
}