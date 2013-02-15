//
//  State.h
//  IM-Big-Devil
//
//  Created by Yifeng Wu on 15/12/12.
//
//

#ifndef __IM_Big_Devil__State__
#define __IM_Big_Devil__State__

#include <iostream>
#include "Telegram.h"

template <class entity_type>
class State {
public:
    virtual ~State() {}
            
    virtual void enter(entity_type *boss) = 0;
    virtual void execute(entity_type *boss, float dt) = 0;
    virtual void exit(entity_type *boss) = 0;
    
    virtual bool onMessage(entity_type *entity, const Telegram *telegram) = 0;
};


#endif /* defined(__IM_Big_Devil__State__) */
