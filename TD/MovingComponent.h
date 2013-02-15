//
//  MovingComponent.h
//  TD
//
//  Created by Yifeng Wu on 25/12/12.
//
//

#ifndef __TD__MovingComponent__
#define __TD__MovingComponent__

#include <iostream>
#include "cocos2d.h"
#include "ComponentBase.h"

class BaseGameEntity;

enum SpeedLevel {
    Slow = 1,
    Normal = 2,
    Fast = 3,
    
    UltraFast = 8,
    };

/**
 @brief This component handles the moving issures for BaseGameEntity.
 
 It provides an update method to be called by the owner.
 */
class MovingComponent : public ComponentBase {
    CC_SYNTHESIZE(cocos2d::CCPoint, m_uTargetPosition, TargetPosition);
    
    CC_SYNTHESIZE(SpeedLevel, m_eSpeedLevel, SpeedLevel);
    
    // weak reference
    CC_SYNTHESIZE_READONLY(BaseGameEntity *, m_pAgent, agent);
    
public:
    //
    // Construction && Deconstruction
    //
    ~MovingComponent();
    
    static MovingComponent *create(BaseGameEntity *agent, SpeedLevel speedLevel);
    
    bool initWithAgent(BaseGameEntity *agent, SpeedLevel speedLevel);
    
    //
    // Logics
    //
    
    // needs to be called explicitly by agent
    virtual void update(float dt);
};

#endif /* defined(__TD__MovingComponent__) */
