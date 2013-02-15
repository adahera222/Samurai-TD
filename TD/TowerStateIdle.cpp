//
//  TowerStateIdle.cpp
//  TD
//
//  Created by Yifeng Wu on 05/01/13.
//
//

#include "TowerStateIdle.h"
#include "Tower.h"
#include "TowerStateFighting.h"
#include "MessageTypes.h"
#include "GameModel.h"

static TowerStateIdle *sg_pState;

TowerStateIdle *TowerStateIdle::instance() {
    if (!sg_pState) {
        sg_pState = new TowerStateIdle();
    }
    return sg_pState;
}


void TowerStateIdle::purge() {
    CC_SAFE_DELETE(sg_pState);
}


void TowerStateIdle::enter(Tower *boss) {
    
}


void TowerStateIdle::execute(Tower *boss, float dt) {
    
}


void TowerStateIdle::exit(Tower *boss) {
    
}


bool TowerStateIdle::onMessage(Tower *tower, const Telegram *telegram) {
    if (tower->getArchitecture()->getType() == kEmptyTower) {
        return false;
    }
    
    switch (telegram->message) {
        case kMessageCollide:
            tower->changeState(TowerStateFighting::instance());
            
            return false;   // to let global state handle this message on purpose, adding the sender to targets of the tower
    }
    return false;
}