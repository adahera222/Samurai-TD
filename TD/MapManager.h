//
//  MapManager.h
//  TD
//
//  Created by Yifeng Wu on 29/12/12.
//
//

#ifndef __TD__MapManager__
#define __TD__MapManager__

#include <iostream>
#include "cocos2d.h"


/**
 * MapManager stores information about the map.
 */
class MapManager : public cocos2d::CCObject {
    cocos2d::CCSize m_uMapSize;
    
    CC_SYNTHESIZE(cocos2d::CCPoint, m_uMapLocation, MapLocation);
        
    CC_SYNTHESIZE_READONLY(cocos2d::CCDictionary *, m_pWayPoints, WayPoints);
    
    CC_SYNTHESIZE_READONLY(cocos2d::CCArray *, m_pTowerSlots, TowerSlots);
    
    CC_SYNTHESIZE_READONLY(cocos2d::CCDictionary *, m_pSpawnPoints, SpawnPoints);
    
    CC_SYNTHESIZE(bool, m_bAllowTower, AllowTower);
    
public:
    ~MapManager();
    
    CREATE_FUNC(MapManager);
    
    bool init();
    
    cocos2d::CCPoint boundGamingLayer(const cocos2d::CCPoint &position) const;
    
    inline cocos2d::CCPoint convertToGameCoord(const cocos2d::CCPoint &position) const {
        return ccpSub(position, m_uMapLocation);
    }
    
    
    void setTiledMap(cocos2d::CCTMXTiledMap *tiledMap);
    
    cocos2d::CCPoint getWayPointForKey(int key) const ;
    
    cocos2d::CCPoint &getSpawnPointForKey(int key) const;
};

#endif /* defined(__TD__MapManager__) */
