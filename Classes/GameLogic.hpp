//
//  GameLogic.hpp
//  12Tiles
//
//  Created by Riya.Liel on 2016/09/10.
//
//

#ifndef GameLogic_hpp
#define GameLogic_hpp

#include "TileController.hpp"

#include <memory>

class GameLogic {
public:
    GameLogic(const std::shared_ptr<TileController>& controller);
    
    bool isCleared();
    bool isTileMovable();
    void selectTile(libspiral::Index index);
    void purge();
    
    static bool isVaildIndex(libspiral::Index index);
    
    std::function<void()> onSelectInvalidTile;
    
private:
    std::shared_ptr<TileController> _tileController;
    std::pair<libspiral::Index, NumTile*> _selectedTile;
};

#endif /* GameLogic_hpp */
