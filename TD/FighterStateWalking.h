//
//  FighterStateWalking.h
//  TD
//
//  Created by Yifeng Wu on 01/01/13.
//
//

#ifndef __TD__FighterStateWalking__
#define __TD__FighterStateWalking__

#include <iostream>
#include "State.h"

class Fighter;

class FighterStateWalking : public State<Fighter> {
    
public:
    static FighterStateWalking *instance();
    
    void enter(Fighter *boss);
    void execute(Fighter *boss, float dt);
    void exit(Fighter *boss) ;
    
    bool onMessage(Fighter * entity, const Telegram *telegram);
};

#endif /* defined(__TD__FighterStateWalking__) */
