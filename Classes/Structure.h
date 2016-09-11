//
//  Structure.h
//  12Tiles
//
//  Created by Riya.Liel on 2016/09/11.
//
//

#ifndef Structure_h
#define Structure_h

#include "Constants.h"
#include <vector>

struct MoveTask {
    float elapsedTime;
    libspiral::Index current;
    NumTile* tile;
    std::vector<libspiral::Index> path;
};

#endif /* Structure_h */
