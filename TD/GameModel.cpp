//
//  GameModel.cpp
//  TD
//
//  Created by Yifeng Wu on 26/12/12.
//
//

#include "GameModel.h"
#include "AWLuaHelper.h"
#include "Figher.h"
#include "Tower.h"

USING_NS_CC;

static GameModel *sg_pSharedGameModel;

// ------------------------------
// Construction && Deconstruction - BEGIN
// ------------------------------

GameModel::~GameModel() {
    CC_SAFE_RELEASE_NULL(m_pEntityManager);
    CC_SAFE_RELEASE_NULL(m_pMapManager);
    CC_SAFE_RELEASE_NULL(m_pProjectileManager);
    CC_SAFE_RELEASE_NULL(m_pPopupMenu);
    CC_SAFE_RELEASE_NULL(m_pWaveManager);
    CC_SAFE_RELEASE_NULL(m_pAnimManager);
}


void GameModel::purge() {
    CC_SAFE_DELETE(sg_pSharedGameModel);
}

// --------------
// Configuration
// --------------
void GameModel::configGameModel(CCLayer *gamePlayScene, int level) {
    CCAssert(gamePlayScene, "--- No game play scene");
    
    if (!sg_pSharedGameModel) {
        sg_pSharedGameModel = new GameModel;
    }
    
    // ---------Load data from file-----------
    
    CCString *filename = CCString::createWithFormat("level_%d.lua", level);
    
    awExecuteLuaFile(filename->getCString());
    
    const char *framesFile = awGetLuaString("frames_file");
    const char *texturesFile = awGetLuaString("textures_file");
    const char *map_file = awGetLuaString("map_file");
    
    
    // Graphics
    configGraphicResource(gamePlayScene, framesFile, texturesFile);
    
    // Animation Manager
    sg_pSharedGameModel->setAnimationManager(AnimationManager::create());
    
    // Map && MapManager
    // ---------------------
    CCTMXTiledMap *tiledMap = CCTMXTiledMap::create(map_file);
    gamePlayScene->addChild(tiledMap, -1);  // Add to game scene
    
    // Unlock Towers & Fighters
    configTowers();
    configFighters();
    
    // Waves && WaveManager
    int numWaves = awGetLuaInt("num_waves");
    sg_pSharedGameModel->setWaveManager(WaveManager::create(configWaves(numWaves)));
    
    sg_pSharedGameModel->init();
    sg_pSharedGameModel->setTiledMap(tiledMap);
}


void GameModel::configGraphicResource(CCLayer *gamePlayScene, const char *framesFile, const char *texturesFile) {
    CCLog("---frame file: %s", framesFile);
    CCLog("---texture file: %s", texturesFile);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(framesFile);
    CCSpriteBatchNode *batch = CCSpriteBatchNode::create(texturesFile);
    sg_pSharedGameModel->setBatch(batch);
    gamePlayScene->addChild(batch);     // Add to game scene
}


CCArray *GameModel::configWaves(int numWaves) {
    
    lua_State *state = CCLuaEngine::defaultEngine()->getLuaState();
    CCArray *waves = CCArray::create();
    
    for (int i=0; i<numWaves; i++) {
        CCString *waveStr = CCString::createWithFormat("wave_%d", i);
        awSetLuaTable(state, waveStr->getCString());
        
        FighterType type = (FighterType)awGetLuaIntFromTable(state, "enemy_type");
        int num = awGetLuaIntFromTable(state, "enemy_num");
        float timeFromLastWave = awGetLuaDoubleFromTable(state, "spawn_time_from_last_wave");
        float interval = awGetLuaDoubleFromTable(state, "spawn_interval");
        int spawnPoint = awGetLuaIntFromTable(state, "spawn_point");
        
        Wave *wave = Wave::create(type, num, timeFromLastWave, interval, spawnPoint);
        waves->addObject(wave);
    }
    
    return waves;
}


void GameModel::configFighters() {
    lua_State *state = CCLuaEngine::defaultEngine()->getLuaState();
    awSetLuaTable(state, "fighters_unlocked");
    
    int numFightersUnlocked = awGetLuaIntFromTable(state, "num_unlocked");
    for (int i=0; i<numFightersUnlocked; i++) {
        awSetLuaTable(state, "fighters_unlocked");  // Because awGetLua**FromTable assumes the table is at the bottom, but everytime creates a tower/fighter, the stack will be reset.

        CCString *ftStr = CCString::createWithFormat("fighter_%d", i);
        FighterType ft = (FighterType)awGetLuaIntFromTable(state, ftStr->getCString());
        Breed::configModel(ft);
    }
}

void GameModel::configTowers() {
    lua_State *state = CCLuaEngine::defaultEngine()->getLuaState();
    awSetLuaTable(state, "towers_unlocked");

    int numTowersUnlocked = awGetLuaIntFromTable(state, "num_unlocked");
    for (int i=0; i<numTowersUnlocked; i++) {
        awSetLuaTable(state, "towers_unlocked");    // Because awGetLua**FromTable assumes the table is at the bottom, but everytime creates a tower/fighter, the stack will be reset.
        CCString *ttStr = CCString::createWithFormat("tower_%d", i);
        TowerType tt = (TowerType)awGetLuaIntFromTable(state, ttStr->getCString());
        Architecture::configModel(tt);
    }
}


GameModel *GameModel::instance() {
    CCAssert(sg_pSharedGameModel, "--- No game model !");
    
    return sg_pSharedGameModel;
}


bool GameModel::init() {
    m_pEntityManager = EntityManager::create();
    m_pEntityManager->retain();
    
    m_pMapManager = MapManager::create();
    m_pMapManager->setAllowTower(false);    // testing
    m_pMapManager->retain();
    
    m_pProjectileManager = ProjectileManager::create();
    m_pProjectileManager->retain();
    
    m_pPopupMenu = PopupMenu::create();
    m_pPopupMenu->retain();
    
    return true;
}
// END


// ------------------------------
// Functions
// ------------------------------
CCLayer *GameModel::getGamePlayScene() {
    return (CCLayer *)m_pBatch->getParent();
}


bool GameModel::handleMessage(const Telegram *telegram) {
    switch (telegram->message) {
        case kMessageIAmDying:
        {
            m_pWaveManager->enemyDied();
            return true;
        }

    }
    return false;
}

void GameModel::update(float dt) {
    m_pEntityManager->update(dt);
    m_pWaveManager->update(dt);
}

// ------------------------------
// APIs - BEGIN
// ------------------------------

// --------------
// Entity Manager
void GameModel::registerEntity(BaseGameEntity *entity) {
    m_pEntityManager->registerEntity(entity);
}


void GameModel::removeEntity(BaseGameEntity *entity) {
    m_pEntityManager->removeEntity(entity);
}


BaseGameEntity *GameModel::getEntityForID(int ID) const {
    return m_pEntityManager->getEntityForID(ID);
}


// ------------
// Map Manager
CCPoint GameModel::boundGamingLayer(const CCPoint &position) const {
    return m_pMapManager->boundGamingLayer(position);
}


CCPoint GameModel::convertToGameCoord(const cocos2d::CCPoint &position) const {
    return m_pMapManager->convertToGameCoord(position);
}


void GameModel::setTiledMap(cocos2d::CCTMXTiledMap *tiledMap) {
    m_pMapManager->setTiledMap(tiledMap);
}


CCPoint GameModel::getWayPointForKey(int key) const {
    return m_pMapManager->getWayPointForKey(key);
}

CCPoint &GameModel::getSpawnPointForKey(int key) const {
    return m_pMapManager->getSpawnPointForKey(key);
}

// ------------
void GameModel::enemyDied() {
    m_pWaveManager->enemyDied();
}