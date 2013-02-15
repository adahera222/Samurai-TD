//
//  ComponentBase.h
//  TD
//
//  Created by Yifeng Wu on 06/01/13.
//
//

#ifndef __TD__ComponentBase__
#define __TD__ComponentBase__

#include <iostream>
#include "cocos2d.h"

class BaseGameEntity;

//---------------------
// Component Types
//---------------------
enum ComponentTypes {
    kShootingComponent = 1,
    kStateMachineComponent = 2,
    kTouchComponent = 3,
    kMovingComponent = 4,
    kCollisionComponent = 5,
    };


//---------------------
// Component Delegate
//---------------------
class ComponentBase : public cocos2d::CCObject {
protected:
    CC_SYNTHESIZE_READONLY(ComponentTypes, m_eType, Type);

    BaseGameEntity *m_pAgent;
    
public:
    /**
     * This is the method to be called before the agent is deleted.
     * If the component was retained earlier by object other than agent, this is the proper place to release it.
     */
    virtual void clean() {};
};

#endif /* defined(__TD__ComponentBase__) */
