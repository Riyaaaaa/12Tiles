//
//  GameManager.hpp
//  12Tiles
//
//  Created by Riya.Liel on 2016/09/08.
//
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include "SpiralLibrary/Cocos2d/GameManagerBase.hpp"
#include "GameScene.h"
#include "TileController.hpp"
#include <memory>

#include "cocos2d.h"

class GameManager : public libspiral::GameManagerBase<GameManager, GameScene> {
public:
    void runScene() override;
    void update(float delta) override;
    
    void spawnTile();
   
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* e);
    
private:
    std::unique_ptr<TileController> _tileController;
};

#endif /* GameManager_hpp */
