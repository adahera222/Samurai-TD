//
//  CollisionManager.h
//  TD
//
//  Created by Yifeng Wu on 25/12/12.
//
//

#ifndef __TD__CollisionManager__
#define __TD__CollisionManager__

#include <iostream>
#include "cocos2d.h"
#include "CellSpacePartition.h"

//class BaseGameEntity;
class CollisionComponent;

class CollisionManager : public cocos2d::CCObject {
    CellSpacePartition *m_pPartition;
    
    cocos2d::CCArray *m_pEntities;
    
public:
    //
    // Construction && Deconstruction
    //
    ~CollisionManager();
    
    bool init();
    
    static CollisionManager *instance();
    
    // need to be called when the collision manager is no longer needed, like return to the main menu.
    static void purge();
    
    //
    // Functions
    //
    void registerEntity(CollisionComponent *entity);

    
    void removeEntity(CollisionComponent *entity);

    void update(float dt);
};

#endif /* defined(__TD__CollisionManager__) */
