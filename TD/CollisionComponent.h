//
//  CollisionComponent.h
//  TD
//
//  Created by Yifeng Wu on 16/01/13.
//
//

#ifndef __TD__CollisionComponent__
#define __TD__CollisionComponent__

#include <iostream>
#include "ComponentBase.h"
#include "AWArray.h"


class CollisionComponent : public ComponentBase {
    CC_SYNTHESIZE(double, m_dCollisionRadius, CollisionRadius);
    CC_SYNTHESIZE(double, m_dQueryRadius, QueryRadius);
    CC_SYNTHESIZE(bool, m_bIsActive, IsActive);
    
    // This array holds the entities that is currently (at this frame) collided with the agent.
    // NOTE: the entities are stored using their ID.
    CC_SYNTHESIZE_READONLY(AWArray *, m_pEntitiesCollided, EntitiesCollied);
    
public:
    
// Construction && Deconstruction
//-----------------------------------
    virtual ~CollisionComponent();
    
    static CollisionComponent *create(BaseGameEntity *agent, double queryR, double collisionR);
    
    bool init(BaseGameEntity *agent, double queryR, double collisionR);
    
    void clean();

// Logics
//-----------------------------------
    const cocos2d::CCPoint &getOldPosition() const;
    const cocos2d::CCPoint &getPosition() const;
    void collideWith(int colliderID);
    
    unsigned int getID() const;
};

#endif /* defined(__TD__CollisionComponent__) */
