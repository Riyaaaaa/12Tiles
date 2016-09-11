#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include <functional>

class GameScene : public cocos2d::Scene
{
public:
    static GameScene* createScene();
    virtual bool init();
    
    void initLisener();
    
    void awake();
    
    std::function<bool(cocos2d::Touch*, cocos2d::Event*)> onTouchBegan;
    std::function<void(cocos2d::Touch*, cocos2d::Event*)> onTouchMoved;
    std::function<void(cocos2d::Touch*, cocos2d::Event*)> onTouchEnded;
    std::function<void(cocos2d::Touch*, cocos2d::Event*)> onTouchCancelled;
    
private:
    cocos2d::Sprite* _bg;
    CC_SYNTHESIZE_READONLY(cocos2d::ui::Button*, _pauseButton, PauseButton);
    CC_SYNTHESIZE_READONLY(cocos2d::EventListenerTouchOneByOne*, _touchListener, TouchListener);
};

#endif // __GAME_SCENE_H__
