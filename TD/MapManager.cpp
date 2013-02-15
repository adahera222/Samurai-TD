//
//  MapManager.cpp
//  TD
//
//  Created by Yifeng Wu on 29/12/12.
//
//

#include "MapManager.h"
#include "GameModel.h"

#include "Tower.h"

USING_NS_CC;


MapManager::~MapManager() {
    CC_SAFE_RELEASE_NULL(m_pWayPoints);
    CC_SAFE_RELEASE_NULL(m_pSpawnPoints);
}

bool MapManager::init() {
    m_bAllowTower = true;
    
    m_pWayPoints = CCDictionary::create();
    m_pWayPoints->retain();
        
    m_pSpawnPoints = CCDictionary::create();
    m_pSpawnPoints->retain();
    
    return true;
}


CCPoint MapManager::boundGamingLayer(const cocos2d::CCPoint &position) const {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint newPos = position;
    
    float maxX = m_uMapSize.width - winSize.width;
    float maxY = m_uMapSize.height - winSize.height;
    
    newPos.x = MAX(newPos.x, 0);
    newPos.y = MAX(newPos.y, 0);
    newPos.x = MIN(newPos.x, maxX);
    newPos.y = MIN(newPos.y, maxY);
    
    return newPos;
}


void MapManager::setTiledMap(cocos2d::CCTMXTiledMap *tileMap) {
    //m_pTiledMap = tileMap;
    
    CCSize mapSize = tileMap->getMapSize();
    CCSize tileSize = tileMap->getTileSize();
    m_uMapSize.height = mapSize.height * tileSize.height;
    m_uMapSize.width = mapSize.width * tileSize.width;
    
    // Way Points
    // -------------------
    
    CCTMXObjectGroup *group = tileMap->objectGroupNamed("WayPoint");
    int numWayPoints = group->getObjects()->count();
    CCDictionary *wayPoint;
    for (int i=0; i<numWayPoints; i++) {
        CCString *str = CCString::createWithFormat("way_point_%d", i);
        wayPoint = group->objectNamed(str->getCString());
                
        int x = atoi(wayPoint->valueForKey("x")->getCString());
        int y = atoi(wayPoint->valueForKey("y")->getCString());
        
        CCPoint *newWayPoint = new CCPoint(x, y);   // need to be deleted later
        m_pWayPoints->setObject(newWayPoint, i);
    }
    
    // Tower Slots
    // -------------------
    
    if (m_bAllowTower) {
        CCTMXObjectGroup *slotGroup = tileMap->objectGroupNamed("TowerSlot");
        int numTowerSlots = slotGroup->getObjects()->count();
        //CCLog("---count: %d", numTowerSlots);
        
        CCDictionary *slots;
        for (int i=0; i<numTowerSlots; i++) {
            CCString *str = CCString::createWithFormat("tower_slot_%d", i);
            slots = slotGroup->objectNamed(str->getCString());
            
            //CCLog("--- %d", i);
            
            int x = atoi(slots->valueForKey("x")->getCString());
            int y = atoi(slots->valueForKey("y")->getCString());
            
            CCPoint pos = ccp(x, y);

            Tower *t = Tower::create(kEmptyTower, kPlayer);
            GameModel::instance()->registerEntity(t);
            t->setPosition(pos);
        }
    }
    
    // Spawn Points
    // -------------------
    
    CCTMXObjectGroup *spawnPointGroup = tileMap->objectGroupNamed("SpawnPoint");
    int numSpawnPoint = spawnPointGroup->getObjects()->count();
    
    CCDictionary *points;
    for (int i=0; i<numSpawnPoint; i++) {
        CCString *str = CCString::createWithFormat("spawn_point_%d", i);
        points = spawnPointGroup->objectNamed(str->getCString());
        
        int x = atoi(points->valueForKey("x")->getCString());
        int y = atoi(points->valueForKey("y")->getCString());
        
        CCPoint *spawnPoint = new CCPoint(x, y);
        m_pSpawnPoints->setObject(spawnPoint, i);
    }
     
}


CCPoint MapManager::getWayPointForKey(int key) const {
    if (key >= m_pWayPoints->count()) { // if key is greater than number of waypoints, return (-1, -1).
        return ccp(-1, -1);
    }
    
    CCPoint *wp = (CCPoint *)m_pWayPoints->objectForKey(key);
    CCPoint retVal;
    retVal.x = wp->x;
    retVal.y = wp->y;
    return retVal;
}


CCPoint &MapManager::getSpawnPointForKey(int key) const {
    CCPoint *wp = (CCPoint *)m_pSpawnPoints->objectForKey(key);
    return *wp;
}