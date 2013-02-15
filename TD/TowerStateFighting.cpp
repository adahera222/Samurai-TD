//
//  TowerStateFighting.cpp
//  TD
//
//  Created by Yifeng Wu on 05/01/13.
//
//

#include "TowerStateFighting.h"
#include "Tower.h"
#include "GameModel.h"
#include "TowerStateIdle.h"

USING_NS_CC;

static TowerStateFighting *sg_pState;

TowerStateFighting *TowerStateFighting::instance() {
    if (!sg_pState) {
        sg_pState = new TowerStateFighting();
    }
    return sg_pState;
}


void TowerStateFighting::purge() {
    CC_SAFE_DELETE(sg_pState);
}


void TowerStateFighting::enter(Tower *boss) {
    
}


void TowerStateFighting::execute(Tower *boss, float dt) {
    if (boss->getTargets()->size() > 0) {
        AW_GET_COMPONENT_FROM(boss, ShootingComponent)->shoot(dt, boss->getArchitecture()->getProjectileType(), boss->getArchitecture()->getAttackInterval());
    }
    else {
        boss->changeState(TowerStateIdle::instance());
    }
}


void TowerStateFighting::exit(Tower *boss) {
    
}


bool TowerStateFighting::onMessage(Tower *tower, const Telegram *telegram) {
    switch (telegram->message) {
        case kMessageIAmDying:
            tower->getTargets()->removeData(telegram->sender);
            return true;
    }
    
    return false;
}