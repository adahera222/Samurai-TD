//
//  MoveAction.h
//  TD
//
//  Created by Yifeng Wu on 26/01/13.
//
//

#ifndef __TD__MoveAction__
#define __TD__MoveAction__

#include <iostream>
#include "Action.h"


class MoveAction : public Action {
    CC_SYNTHESIZE(cocos2d::CCPoint, m_uTargetPos, TargetPosition);
    
    CC_SYNTHESIZE(int, m_iSpeedLev, SpeedLevel);
    
    
public:
    static MoveAction *create(BaseGameEntity *agent, const cocos2d::CCPoint &targetPos, int speedLev, bool blocking);
    
    bool init(BaseGameEntity *agent, const cocos2d::CCPoint &targetPos, int speedLev, bool blocking);
    
    virtual void update(float dt);
};

#endif /* defined(__TD__MoveAction__) */
