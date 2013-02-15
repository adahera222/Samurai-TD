//
//  GameModel.h
//  TD
//
//  Created by Yifeng Wu on 26/12/12.
//
//

#ifndef __TD__GameModel__
#define __TD__GameModel__

#include <iostream>
#include "cocos2d.h"
#include "EntityManager.h"
#include "MapManager.h"
#include "ProjectileManager.h"
#include "PopupMenu.h"
#include "WaveManager.h"
#include "AnimationManager.h"

class GameModel : public cocos2d::CCObject {
    CC_SYNTHESIZE_READONLY(EntityManager *, m_pEntityManager, EntityManager);
    
    CC_SYNTHESIZE_READONLY(MapManager *, m_pMapManager, MapManager);
    
    CC_SYNTHESIZE_READONLY(ProjectileManager *, m_pProjectileManager, ProjectileManager);
    
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatch, Batch);
    
    CC_SYNTHESIZE_READONLY(PopupMenu *, m_pPopupMenu, PopupMenu);
    
    // It is created during cnfiguration.
    CC_SYNTHESIZE_RETAIN(WaveManager *, m_pWaveManager, WaveManager);
    
    CC_SYNTHESIZE_RETAIN(AnimationManager *, m_pAnimManager, AnimationManager);
    
// ------------------------------
// Configuration
// ------------------------------
    static void configFighters();
    static void configTowers();
    static void configWaves();
    static void configGraphicResource(cocos2d::CCLayer *gamePlayScene, const char *framesFile, const char *texturesFile);
    static cocos2d::CCArray *configWaves(int numWaves);
public:
    /**
     * This method is used to config the game settings, such as level information.
     
     * It should be called at the game play scene at the very beginning.
     */
    static void configGameModel(cocos2d::CCLayer *gamePlayScene, int level);
    
    
public:
// ------------------------------
// Construction && Deconstruction
// ------------------------------
    ~GameModel();
    
    // Need to be called when GameModel is no longer needed, like returning to the main menu.
    static void purge();
    
    
    
    static GameModel *instance();

    bool init();
    
// ------------------------------
// Functions (encapsulate components' functions for convenience's sake)
// ------------------------------

    bool handleMessage(const Telegram *telegram);
    
    cocos2d::CCLayer *getGamePlayScene();
    
    void update(float dt);
    
// ------------------------------
// Entity Manager
// ------------------------------
    void registerEntity(BaseGameEntity *entity);
    void removeEntity(BaseGameEntity *entity);
    BaseGameEntity *getEntityForID(int ID) const ;
    
// ------------------------------
// Map Manager
// ------------------------------
    cocos2d::CCPoint boundGamingLayer(const cocos2d::CCPoint &position) const;
    cocos2d::CCPoint convertToGameCoord(const cocos2d::CCPoint &position) const;
    void setTiledMap(cocos2d::CCTMXTiledMap *tiledMap);
    cocos2d::CCPoint getWayPointForKey(int key) const ;
    cocos2d::CCPoint &getSpawnPointForKey(int key) const;
    
// ------------------------------
// Popup Menu
// ------------------------------
    
// ------------------------------
// Entity Manager
// ------------------------------
    void enemyDied();
};



#endif /* defined(__TD__GameModel__) */
