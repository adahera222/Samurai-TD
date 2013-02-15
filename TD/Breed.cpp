//
//  Breed.cpp
//  TD
//
//  Created by Yifeng Wu on 25/12/12.
//
//

#include "Breed.h"
#include "AWLuaHelper.h"
#include "GameModel.h"

#include "lua/cocos2dx_support/CCLuaEngine.h"

USING_NS_CC;



//
// Construction && Deconstruction - BEGIN
//

static cocos2d::CCDictionary *sg_pBreedModels;


Breed::~Breed() {
    
}


void Breed::purgeBreedModelsData() {
    CC_SAFE_RELEASE_NULL(sg_pBreedModels);
}


// Models

Breed *Breed::createModel(FighterType type) {
    Breed *breed = new Breed();
    if (breed && breed->initModel(type)) {
        breed->autorelease();
        return breed;
    }
    CC_SAFE_DELETE(breed);
    return NULL;
}


bool Breed::initModel(FighterType type) {
    m_eType = type;
    
    CCString *typeString = CCString::createWithFormat("fighter_%d", type);
    readDataFromFile("breedInfo.lua", typeString->getCString());
    
    readAnimationFromFile("breedInfo.lua", type);
    
    /*
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();

    CCSpriteFrame *frame1 = cache->spriteFrameByName("sword_walk_0.png");
    CCSpriteFrame *frame2 = cache->spriteFrameByName("sword_walk_1.png");
    CCSpriteFrame *frame3 = cache->spriteFrameByName("sword_walk_2.png");
    
    CCAnimation *anim = CCAnimation::createWithSpriteFrames(CCArray::create(frame1, frame2, frame3, frame3, frame3, NULL), 0.1f);
    
    CCAnimationCache::sharedAnimationCache()->addAnimation(anim, "sword_walk");
    */
    return true;
}


void Breed::readDataFromFile(const char *fileName, const char *tableKey) {
    static bool executed = false;
    if (!executed) {
        CCLog("---executed");
        awExecuteLuaFile(fileName);
        executed = true;
    }
    
    CCLuaEngine *pEngine = CCLuaEngine::defaultEngine();
    pEngine->cleanStack();
    
    lua_State *state = pEngine->getLuaState();
    
    awSetLuaTable(state, tableKey);
    
    m_sName = awGetLuaStringFromTable(state, "name");
    m_sSpriteName = awGetLuaStringFromTable(state, "sprite_name");
    
    m_dGuardingRadius = awGetLuaDoubleFromTable(state, "guarding_radius");
    m_dBodyRadius = awGetLuaDoubleFromTable(state, "body_radius");
    
    m_iMaxHealth = awGetLuaIntFromTable(state, "max_health");
    m_iSpeedLevel = awGetLuaIntFromTable(state, "speed_level");
}


void Breed::readAnimationFromFile(const char *fileName, FighterType type) {
    CCString *behaviorsStr = CCString::createWithFormat("fighter_%d_behaviors", type);
    
    
    lua_State *state = awGetLuaState();
    awSetLuaTable(state, behaviorsStr->getCString());
    
    int numOfBehaviors = awGetLuaIntFromTable(state, "num_of_behaviors");
    
    CCArray *behaviorStrs = CCArray::create();
    
    for (int i=0; i<numOfBehaviors; i++) {
        CCString *behaviorIndexStr = CCString::createWithFormat("behavior_%d", i);
        
        const char *behavior = awGetLuaStringFromTable(state, behaviorIndexStr->getCString());
        
        CCString *behaviorStr = CCString::createWithFormat("fighter_%d_%s", type, behavior);
        behaviorStrs->addObject(behaviorStr);
    }
    
    for (int i=0; i<numOfBehaviors; i++) {
        CCString *behaviorStr = (CCString *)behaviorStrs->objectAtIndex(i);
        awSetLuaTable(state, behaviorStr->getCString());

        int numOfFrames = awGetLuaIntFromTable(state, "num_of_frames");
        
        CCArray *frames = CCArray::create();
        AWArray numsOfFrame;
        for (int j=0; j<numOfFrames; j++) {
            CCString *frameStr = CCString::createWithFormat("frame_%d", j);
            const char *frameName = awGetLuaStringFromTable(state, frameStr->getCString());

            CCSpriteFrame *frameToAdd = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName);
            frames->addObject(frameToAdd);
            
            CCString *numOfFrameStr = CCString::createWithFormat("nums_of_frame_%d", j);
            int numOfFrame = awGetLuaIntFromTable(state, numOfFrameStr->getCString());
            numsOfFrame.push(numOfFrame);
        }
        
        const char *name = awGetLuaStringFromTable(state, "name");
        
        GameModel::instance()->getAnimationManager()->addAnimation(frames, &numsOfFrame, 0.1f, name);
    }
    
    
}


void Breed::configModel(FighterType type) {
    if (!sg_pBreedModels) {
        sg_pBreedModels = CCDictionary::create();
        sg_pBreedModels->retain();      // need to release !!
    }
    
    Breed *model = Breed::createModel(type);
    sg_pBreedModels->setObject(model, type);
}



/*
// this function should only be implemented once
void Breed::createBreedModels(FighterType *types, int size) {
    if (sg_pBreedModels) {
        return ;
    }
    
    sg_pBreedModels = CCDictionary::create();
    sg_pBreedModels->retain();  // need to release !!!
    
    for (int i=0; i<size; i++) {
        Breed *aBreed = Breed::createModel(types[i]);
        sg_pBreedModels->setObject(aBreed, types[i]);
    }
}
*/

Breed *Breed::getBreedForType(FighterType type) {
    Breed *retBreed = (Breed *)sg_pBreedModels->objectForKey(type);
    if (!retBreed) {
        CCLog("--- breed for type: %d has not been added!", type);
        retBreed = createModel(type);
        sg_pBreedModels->setObject(retBreed, type);
    }
    return retBreed;
}

// END


