//
//  TowerStateIdle.h
//  TD
//
//  Created by Yifeng Wu on 05/01/13.
//
//

#ifndef __TD__TowerStateIdle__
#define __TD__TowerStateIdle__

#include <iostream>
#include "State.h"

class Tower;

class TowerStateIdle : public State<Tower> {
public:
    static TowerStateIdle *instance();
    
    static void purge();
    
    void enter(Tower *boss);
    void execute(Tower *boss, float dt);
    void exit(Tower *boss);
    
    bool onMessage(Tower *tower, const Telegram *telegram);
};

#endif /* defined(__TD__TowerStateIdle__) */
