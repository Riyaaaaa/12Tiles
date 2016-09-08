//
//  GameManager.hpp
//  12Tiles
//
//  Created by Riya.Liel on 2016/09/08.
//
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include "SingletonBase.hpp"
#include "GameScene.h"

#include "cocos2d.h"

class GameManager : public SingletonBase<GameManager> {
    typedef GameScene scene_t;
public:
    void runScene();
    void update(float delta);
    
private:
    scene_t* running_scene;
};

#endif /* GameManager_hpp */
