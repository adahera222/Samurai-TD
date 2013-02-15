//
//  FighterGlobalState.cpp
//  TD
//
//  Created by Yifeng Wu on 01/01/13.
//
//

#include "FighterGlobalState.h"
#include "Figher.h"
#include "MessageDispatcher.h"
#include "FighterStateWalking.h"

#include "GameModel.h"

USING_NS_CC;

static FighterGlobalState *sg_pFighterGlobalState;


FighterGlobalState *FighterGlobalState::instance() {
    if (!sg_pFighterGlobalState) {
        sg_pFighterGlobalState = new FighterGlobalState();
    }
    return sg_pFighterGlobalState;
}


void FighterGlobalState::enter(Fighter *boss) {
    
}


void FighterGlobalState::execute(Fighter *boss, float dt) {
    if (boss->getCurrentHealth() <= 0) {    // die
        
        boss->setIsActive(false);
        
        if (boss->getController() == kNPC) {
            GameModel::instance()->enemyDied();
        }
        GameModel::instance()->removeEntity(boss);

    }
}


void FighterGlobalState::exit(Fighter *boss) {
    
}


bool FighterGlobalState::onMessage(Fighter *entity, const Telegram *telegram) {
    switch (telegram->message) {
        case kMessageMoveToPosition:
        {
            CCPoint targetPos = *(cocos2d::CCPoint *)(telegram->extraInfo);
            entity->getMovingComponent()->setTargetPosition(targetPos);
            //CCLOG("targetPos: %f, %f", targetPos.x, targetPos.y);
            entity->getStateMachine()->changeState(FighterStateWalking::instance());
        }
            return true;

        case kMessageHit:
        {
            int damage = *((int *)telegram->extraInfo);
            entity->calculateDamage(damage);
        }
            return true;
    }
    return false;
}