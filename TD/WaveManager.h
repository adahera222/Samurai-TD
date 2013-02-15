//
//  WaveManager.h
//  TD
//
//  Created by Yifeng Wu on 15/01/13.
//
//

#ifndef __TD__WaveManager__
#define __TD__WaveManager__

#include <iostream>
#include "cocos2d.h"
#include "Figher.h"

class Wave : public cocos2d::CCObject {
    FighterType m_eEntityType;

    int m_iEntitiesToSpawn;
    int m_iEntitiesLeft;
    
    float m_fSpawnTimeFromLastWave;
    float m_fSpawnInterval;
    int m_iSpawnPoint;
    
    float m_fInterval;
    
public:
    static Wave *create(FighterType type, int num, float timeFromLastWave, float interval, int spawnPoint);
    bool init(FighterType type, int num, float timeFromLastWave, float interval, int spawnPoint);
    
    int getEntitiesLeft();
    void enemyDied();
    
    void spawn(float dt);
};


class WaveManager : public cocos2d::CCObject {
    cocos2d::CCArray *m_pWaves;
    
    CC_SYNTHESIZE_READONLY(Wave *, m_pCurWave, CurrentWave);
    
public:
    ~WaveManager();
    
    static WaveManager *create(cocos2d::CCArray *waves);
    bool initWithWaves(cocos2d::CCArray *waves);
    
    void enemyDied();

    void update(float dt);
};

#endif /* defined(__TD__WaveManager__) */
