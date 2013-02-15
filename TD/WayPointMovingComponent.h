//
//  EnemyMovingComponent.h
//  TD
//
//  Created by Yifeng Wu on 03/01/13.
//
//

#ifndef __TD__WayPointMovingComponent__
#define __TD__WayPointMovingComponent__

#include <iostream>
#include "MovingComponent.h"
#include "Figher.h"

class WayPointMovingComponent : public MovingComponent {
    int curWP;
    
public:
    static WayPointMovingComponent *create(Fighter *agent, SpeedLevel speedLevel);
    bool initWithAgent(Fighter *agent, SpeedLevel speedLevel);
    
    void update(float dt);
};

#endif /* defined(__TD__EnemyMovingComponent__) */
