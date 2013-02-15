//
//  Architecture.cpp
//  TD
//
//  Created by Yifeng Wu on 30/12/12.
//
//

#include "Architecture.h"
#include "AWLuaHelper.h"

USING_NS_CC;

static CCDictionary *sg_pArchitectureModels;


//
// Construction && Deconstruction - BEGIN
//

Architecture::~Architecture() {
    CC_SAFE_DELETE(m_pUpgradables);
}


void Architecture::purgeArchitectureModelsData() {
    CC_SAFE_RELEASE_NULL(sg_pArchitectureModels);
}


Architecture *Architecture::createModel(TowerType type) {
    Architecture *arch = new Architecture();
    if (arch && arch->initModelWithType(type)) {
        arch->autorelease();
        return arch;
    }
    CC_SAFE_DELETE(arch);
    return NULL;
}


bool Architecture::initModelWithType(TowerType type) {
    m_eType = type;
    
    CCString *typeString = CCString::createWithFormat("tower_%d", type);
    m_pUpgradables = new std::vector<TowerType>();
    readDataFromFile("towerInfo.lua", typeString->getCString());
    
    return true;
}


void Architecture::configModel(TowerType type) {
    if (!sg_pArchitectureModels) {
        sg_pArchitectureModels = CCDictionary::create();
        sg_pArchitectureModels->retain();   // need to be released !!!
    }
    //CCLog("--- archi type: %d", type);
    Architecture *model = Architecture::createModel(type);
    sg_pArchitectureModels->setObject(model, type);
}

/*
// this function should only be called once
void Architecture::createArchitectureModels(TowerType *types, int size) {
    if (sg_pArchitectureModels) {
        return ;
    }
    
    sg_pArchitectureModels = CCDictionary::create();
    sg_pArchitectureModels->retain();
    
    for (int i=0; i<size; i++) {
        Architecture *arch = Architecture::createModel(types[i]);
        sg_pArchitectureModels->setObject(arch, types[i]);
    }
}
*/

void Architecture::readDataFromFile(const char *fileName, const char *tableKey) {
    static bool executed = false;
    if (!executed)
        awExecuteLuaFile(fileName);
    
    CCLuaEngine *pEngine = CCLuaEngine::defaultEngine();
    pEngine->cleanStack();
    
    lua_State *state = pEngine->getLuaState();
    
    awSetLuaTable(state, tableKey);
    
    // Set attributes
    
    m_sName = awGetLuaStringFromTable(state, "name");
    m_sSpriteName = awGetLuaStringFromTable(state, "sprite_name");
    
    int numUpgrades = awGetLuaIntFromTable(state, "num_upgrades");
    for (int i=0; i<numUpgrades; i++) {
        CCString *upgradeNString = CCString::createWithFormat("upgrade%d", i);
        TowerType upgradeN = (TowerType)awGetLuaIntFromTable(state, upgradeNString->getCString());
        m_pUpgradables->push_back(upgradeN);
    }
    
    m_iResourceNeeded = awGetLuaIntFromTable(state, "resource_needed");
    
    m_fAttackInterval = awGetLuaDoubleFromTable(state, "attack_interval");
    
    m_eProjectileType = (ProjectileTypes)awGetLuaIntFromTable(state, "projectile_type");
    
    m_sDescription = awGetLuaStringFromTable(state, "description");
    
    m_dGuardingRadius = awGetLuaDoubleFromTable(state, "guarding_radius");
    m_dBodyRadius = awGetLuaDoubleFromTable(state, "body_radius");
}


Architecture *Architecture::getArchitectureForType(TowerType type) {
    Architecture *retArchi = (Architecture *)sg_pArchitectureModels->objectForKey(type);
    if (!retArchi) {
        CCLog("--- architecture for type: %d has not been added!", type);
        retArchi = createModel(type);
        sg_pArchitectureModels->setObject(retArchi, type);
    }
    return retArchi;
}

// END