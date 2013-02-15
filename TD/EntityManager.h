//
//  EntityManager.h
//  TD
//
//  Created by Yifeng Wu on 26/12/12.
//
//

#ifndef __TD__EntityManager__
#define __TD__EntityManager__

#include <iostream>
#include "cocos2d.h"

class BaseGameEntity;


/**
 @brief This class holds the registered game entities.
 
 Only create once.
 */
class EntityManager : public cocos2d::CCObject {
    cocos2d::CCDictionary *m_pIDToEntitiesMap;
    
    //cocos2d::CCArray *m_pEntitiesToAdd;
    
    cocos2d::CCArray *m_pEntitiesToRemove;
    
public:
    //
    // Construction && Deconstruction
    //
    ~EntityManager();
    
    static EntityManager *create();

    bool init();
    
    //
    // Functions
    //
    void registerEntity(BaseGameEntity *entity);

    BaseGameEntity *getEntityForID(int ID) const;

    void removeEntity(BaseGameEntity *entity);
    
    void update(float dt);
};

#endif /* defined(__TD__EntityManager__) */
