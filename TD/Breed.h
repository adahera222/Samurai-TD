//
//  Breed.h
//  TD
//
//  Created by Yifeng Wu on 25/12/12.
//
//

#ifndef __TD__Breed__
#define __TD__Breed__

#include <iostream>
#include "cocos2d.h"
#include "AWArray.h"

class Fighter;


enum FighterType {
    kPeasant = 1,
};




/**
 @brief This class encapsulates the fighter's common attributes, like attack damage.
 */
class Breed : public cocos2d::CCObject {    
    //
    // Fighter Attributes
    //
    CC_SYNTHESIZE_READONLY(const char *, m_sName, Name);
    CC_SYNTHESIZE_READONLY(const char *, m_sSpriteName, SpriteName);
    
    CC_SYNTHESIZE_READONLY(double, m_dGuardingRadius, GuardingRadius);
    CC_SYNTHESIZE_READONLY(double, m_dBodyRadius, BodyRadius);
    
    CC_SYNTHESIZE_READONLY(FighterType, m_eType, Type);
    CC_SYNTHESIZE_READONLY(int, m_iMaxHealth, MaxHealth);
    CC_SYNTHESIZE_READONLY(int, m_iSpeedLevel, SpeedLevel);
            
    static Breed *createModel(FighterType type);
    
    void readDataFromFile(const char *fileName, const char *tableKey);
    
    void readAnimationFromFile(const char *fileName, FighterType type);
    


    
public:
    //
    // Construction && Deconstruction
    //
    virtual ~Breed();
    
    // need to be called when exit the game scene
    static void purgeBreedModelsData();
            
    bool initModel(FighterType type);
    
    static void configModel(FighterType type);
    //static void createBreedModels(FighterType *types, int size);
    
    
    
    // Get the breed model for a specified type
    static Breed *getBreedForType(FighterType type);

};

#endif /* defined(__TD__Breed__) */
