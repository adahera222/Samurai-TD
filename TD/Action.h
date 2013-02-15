//
//  Action.h
//  TD
//
//  Created by Yifeng Wu on 25/01/13.
//
//

#ifndef __TD__Action__
#define __TD__Action__

#include <iostream>
#include "cocos2d.h"
#include "BaseGameEntity.h"

enum ActionTypes {
    kMoveAction = 1,

    };

class Action : public cocos2d::CCObject {
protected:
    CC_SYNTHESIZE(bool, m_bBlocking, Blocking);
    
    CC_SYNTHESIZE(bool, m_bActivated, Activated);
    
    BaseGameEntity *m_pAgent;
    
public:
    virtual void update(float dt) = 0;

};

#endif /* defined(__TD__Action__) */
