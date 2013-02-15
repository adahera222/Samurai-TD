//
//  TowerGlobalState.h
//  TD
//
//  Created by Yifeng Wu on 05/01/13.
//
//

#ifndef __TD__TowerGlobalState__
#define __TD__TowerGlobalState__

#include <iostream>
#include "State.h"

class Tower;

class TowerGlobalState : public State<Tower> {
public:
    static TowerGlobalState *instance();
    
    static void purge();
    
    void enter(Tower *boss);
    void execute(Tower *boss, float dt);
    void exit(Tower *boss);
    
    bool onMessage(Tower *tower, const Telegram *telegram);
};

#endif /* defined(__TD__TowerGlobalState__) */
