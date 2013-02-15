//
//  Architecture.h
//  TD
//
//  Created by Yifeng Wu on 30/12/12.
//
//

#ifndef __TD__Architecture__
#define __TD__Architecture__

#include <iostream>
#include "cocos2d.h"
#include "Projectile.h"

enum TowerType {
    kEmptyTower = 0,
    kArcherTower = 1,
    kArcherTowerLv2 = 2,
    kArcherTowerLv3 = 3,
};

class Architecture : public cocos2d::CCObject {
    //
    // Attributes
    //
    CC_SYNTHESIZE_READONLY(const char *, m_sName, Name);
    CC_SYNTHESIZE_READONLY(const char *, m_sSpriteName, SpriteName);
    CC_SYNTHESIZE_READONLY(TowerType, m_eType, Type);
    CC_SYNTHESIZE_READONLY(std::vector<TowerType> *, m_pUpgradables, Upgradables);
    CC_SYNTHESIZE_READONLY(int, m_iResourceNeeded, ResourceNeeded);
    CC_SYNTHESIZE_READONLY(float, m_fAttackInterval, AttackInterval);
    CC_SYNTHESIZE_READONLY(ProjectileTypes, m_eProjectileType, ProjectileType);
    CC_SYNTHESIZE_READONLY(const char *, m_sDescription, Description);
    
    CC_SYNTHESIZE_READONLY(double, m_dGuardingRadius, GuardingRadius);
    CC_SYNTHESIZE_READONLY(double, m_dBodyRadius, BodyRadius);
    
    static Architecture *createModel(TowerType type);

    
public:
    //
    // Construction && Deconstruction
    //
    virtual ~Architecture();

    // need to be called when exit the game scene
    static void purgeArchitectureModelsData();
    
    bool initModelWithType(TowerType type);
    
    static void configModel(TowerType type);
    //static void createArchitectureModels(TowerType *types, int size);
    
    void readDataFromFile(const char *fileName, const char *tableKey);

    // Get the architecture model for a specified type
    static Architecture *getArchitectureForType(TowerType type);
};

#endif /* defined(__TD__Architecture__) */
