//
//  WaveManager.cpp
//  TD
//
//  Created by Yifeng Wu on 15/01/13.
//
//

#include "WaveManager.h"
#include "Figher.h"
#include "GameModel.h"

USING_NS_CC;

//-----------------------
// Wave Class
//-----------------------

Wave *Wave::create(FighterType type, int num, float timeFromLastWave, float interval, int spawnPoint) {
    Wave *retval = new Wave;
    if (retval && retval->init(type, num, timeFromLastWave, interval, spawnPoint)) {
        retval->autorelease();
        return retval;
    }
    CC_SAFE_DELETE(retval);
    return NULL;
}


bool Wave::init(FighterType type, int num, float timeFromLastWave, float interval, int spawnPoint) {
    m_eEntityType = type;
    m_iEntitiesToSpawn = num;
    m_iEntitiesLeft = num;
    m_fSpawnTimeFromLastWave = timeFromLastWave;
    m_fSpawnInterval = interval;
    m_iSpawnPoint = spawnPoint;
    
    m_fInterval = 0;
    
    return true;
}


int Wave::getEntitiesLeft() {
    return m_iEntitiesLeft;
}


void Wave::spawn(float dt) {
    if (m_fInterval >= m_fSpawnInterval) {
        if (m_iEntitiesToSpawn > 0) {
            //CCLog("---entity num left: %d", m_iEntityNum);
            //CCLog("---spawn");
            Fighter *fighter = Fighter::create(m_eEntityType, kNPC);
            CCPoint pos = GameModel::instance()->getSpawnPointForKey(m_iSpawnPoint);

            GameModel::instance()->registerEntity(fighter);
            fighter->setPosition(pos);
            
            m_iEntitiesToSpawn--;
        }

        m_fInterval = 0;
    }
    
    m_fInterval += dt;
}


void Wave::enemyDied() {
    m_iEntitiesLeft--;
}


//-----------------------
// WaveManager Class
//-----------------------

WaveManager::~WaveManager() {
    CC_SAFE_RELEASE_NULL(m_pWaves);
}


WaveManager *WaveManager::create(CCArray *waves) {
    WaveManager *retval = new WaveManager();
    if (retval && retval->initWithWaves(waves)) {
        retval->autorelease();
        return retval;
    }
    CC_SAFE_DELETE(retval);
    return NULL;
}


bool WaveManager::initWithWaves(CCArray *waves) {
    do {
        // waves should be added in sequence
        m_pWaves = waves;
        m_pWaves->retain();
        
        m_pCurWave = (Wave *)m_pWaves->objectAtIndex(0);
    } while (0);
    
    return true;
}


void WaveManager::enemyDied() {
    m_pCurWave->enemyDied();
    if (m_pCurWave->getEntitiesLeft() <= 0) {
        m_pWaves->removeObject(m_pCurWave);
        
        if (m_pWaves->count() > 0) {    // next wave
            m_pCurWave = (Wave *)m_pWaves->objectAtIndex(0);
        }
        else {
            m_pCurWave = NULL;
            CCLog("--- Win !");
        }
    }
}

void WaveManager::update(float dt) {
    if (m_pCurWave) {
        m_pCurWave->spawn(dt);
    }
}