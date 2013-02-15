//
//  MoveAction.cpp
//  TD
//
//  Created by Yifeng Wu on 26/01/13.
//
//

#include "MoveAction.h"

USING_NS_CC;


MoveAction *MoveAction::create(BaseGameEntity *agent, const cocos2d::CCPoint &targetPos, int speedLev, bool blocking) {
    MoveAction *retval = new MoveAction();
    if (retval && retval->init(agent, targetPos, speedLev, blocking)) {
        retval->autorelease();
        return retval;
    }
    CC_SAFE_DELETE(retval);
    return NULL;
}


bool MoveAction::init(BaseGameEntity *agent, const cocos2d::CCPoint &targetPos, int speedLev, bool blocking) {
    m_pAgent = agent;
    m_uTargetPos = targetPos;
    m_iSpeedLev = speedLev;
    m_bBlocking = blocking;
    
    m_bActivated = false;
    
    return true;
}


void MoveAction::update(float dt) {
    CCPoint pos = m_pAgent->getPosition();
    
    double distSQ = ccpDistanceSQ(m_uTargetPos, pos);
    if (distSQ < 5) {
        m_bActivated = false;
    }
    else {
        m_bActivated = true;
    }
    
    if (m_bActivated) {
        CCPoint direction = ccpSub(m_uTargetPos, pos);
        CCPoint n = ccpNormalize(direction);
        
        double kSpeedTweaker = 0.2;
        double k = m_iSpeedLev * kSpeedTweaker;
        
        n.x *= k;
        n.y *= k;
        
        CCPoint goTo = ccpAdd(pos, n);
        m_pAgent->setPosition(goTo);
    }
}