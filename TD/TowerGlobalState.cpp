//
//  TowerGlobalState.cpp
//  TD
//
//  Created by Yifeng Wu on 05/01/13.
//
//

#include "TowerGlobalState.h"
#include "Tower.h"
#include "MessageTypes.h"
#include "GameModel.h"
#include "Figher.h"

USING_NS_CC;

static TowerGlobalState *sg_pState;

TowerGlobalState *TowerGlobalState::instance() {
    if (!sg_pState) {
        sg_pState = new TowerGlobalState();
    }
    return sg_pState;
}


void TowerGlobalState::purge() {
    CC_SAFE_DELETE(sg_pState);
}


void TowerGlobalState::enter(Tower *boss) {
    
}


void TowerGlobalState::execute(Tower *boss, float dt) {
    
}


void TowerGlobalState::exit(Tower *boss) {
    
}


bool TowerGlobalState::onMessage(Tower *tower, const Telegram *telegram) {
    switch (telegram->message) {    // add sender to targets
        
        case kMessageCollide:
        {
            Fighter *sender = (Fighter *)GameModel::instance()->getEntityForID(telegram->sender);
            if (sender->getController() != tower->getController()) {                
                AWArray *targets = tower->getTargets();
                if (targets->contains(telegram->sender)) {
                    break;
                }
                targets->push(telegram->sender);
                sender->getKillers()->push(tower->getID());
            }
            return true;
        }
            
            
    }
    return false;
}