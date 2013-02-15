//
//  GamePlayLayer.h
//  TD
//
//  Created by Yifeng Wu on 29/12/12.
//
//

#ifndef __TD__GamePlayScene__
#define __TD__GamePlayScene__

#include <iostream>
#include "cocos2d.h"
#include "MapTouchLayer.h"

class BaseGameEntity;

/**
 @brief This is the scene class where the game logic is on.
 
 It includes the following features:
    1. Sprite batch
        All the game entities should add their sprites into the sprite batch, including the map sprite.
 
 */
class GamePlayScene : public cocos2d::CCLayer {
    cocos2d::CCSpriteBatchNode *m_pBatch;
    //cocos2d::CCTMXTiledMap *m_pMap;
    
    MapTouchLayer *m_pTouchLayer;
    
    BaseGameEntity *m_pTarget;
    //BaseGameEntity *m_pTower;
    
public:
    // ------------------------------
    // Construction && Deconstruction
    // ------------------------------
    ~GamePlayScene();
    
    static cocos2d::CCScene *scene();
    
    //GamePlayScene *create(const char *fileImage);
    
    CREATE_FUNC(GamePlayScene);
    
    bool init();
    
    void update(float dt);
    
    // ------------------------------
    // Testing
    // ------------------------------
    //void setTarget(BaseGameEntity *target);
    
    //void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event);
};
#endif /* defined(__TD__GamePlayLayer__) */
