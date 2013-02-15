//
//  FighterGlobalState.h
//  TD
//
//  Created by Yifeng Wu on 01/01/13.
//
//

#ifndef __TD__FighterGlobalState__
#define __TD__FighterGlobalState__

#include <iostream>
#include "State.h"

class Fighter;

class FighterGlobalState : public State<Fighter> {
    
public:
    static FighterGlobalState *instance();
    
    void enter(Fighter *boss);
    void execute(Fighter *boss, float dt);
    void exit(Fighter *boss) ;
    
    bool onMessage(Fighter * entity, const Telegram *telegram);
};


#endif /* defined(__TD__FighterGlobalState__) */
