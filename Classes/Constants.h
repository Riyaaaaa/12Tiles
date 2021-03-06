//
//  Constants.h
//  12Tiles
//
//  Created by Riya.Liel on 2016/09/08.
//
//

#ifndef Constants_h
#define Constants_h

#include "SpiralLibrary/Structure/Index.hpp"
#include "SpiralLibrary/Structure/MultiIndex.hpp"

namespace Constants {
    namespace TileLayout {
        static constexpr int NUMBER_OF_TILES_X = 4;
        static constexpr int NUMBER_OF_TILES_Y = 5;
        static constexpr float DESIGN_SIZE_X = 750;
        static constexpr float DESIGN_SIZE_Y = 1334;
        static constexpr float TILE_SIZE = 150.0f;
        static constexpr float PADDING_X = 30.0f;
        static constexpr float PADDING_Y = 30.0f;
        static constexpr float MARGIN_X = (DESIGN_SIZE_X - (TILE_SIZE * NUMBER_OF_TILES_X + PADDING_X * 2)) / (NUMBER_OF_TILES_X - 1);
        static constexpr float MARGIN_Y = 30.0f;
        
    }
    
    namespace FilePath {
        static constexpr auto MAIN_CSB = "MainScene.csb";
        static constexpr auto GAMEOVER_CSB = "EndTelop.csb";
        static constexpr auto PAUSE_CSB = "Pause.csb";
        static constexpr auto CLEAR_CSB = "ClearTelop.csb";
    }
    
    namespace NodeName {
        static constexpr auto BACKGROUND = "Bg";
        static constexpr auto RETRY_BUTTON = "Retry";
        static constexpr auto END_BUTTON = "End";
        static constexpr auto PAUSE_BUTTON = "Pause";
    }
    
    static constexpr int MAX_VALUE = 12;
    static constexpr float MOVE_DURATION = 0.10f;
    static constexpr float FLIP_DURATION = 0.10f;
    
    static constexpr libspiral::IndexRange<2> TILE_RANGE
    = libspiral::IndexRange<2>(libspiral::Index(0, 0),
                               libspiral::Index(
                                   TileLayout::NUMBER_OF_TILES_X - 1,
                                   TileLayout::NUMBER_OF_TILES_Y - 1));
    
    
}

#endif /* Constants_h */
