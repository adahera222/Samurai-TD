//
//  EnemyMovingComponent.cpp
//  TD
//
//  Created by Yifeng Wu on 03/01/13.
//
//

#include "WayPointMovingComponent.h"
#include "Figher.h"
#include "GameModel.h"
#include "MessageDispatcher.h"

USING_NS_CC;


WayPointMovingComponent *WayPointMovingComponent::create(Fighter *agent, SpeedLevel speedLevel) {
    WayPointMovingComponent *retVal = new WayPointMovingComponent();
    if (retVal && retVal->initWithAgent(agent, speedLevel)) {
        retVal->autorelease();
        return retVal;
    }
    CC_SAFE_DELETE(retVal);
    return NULL;
}


bool WayPointMovingComponent::initWithAgent(Fighter *agent, SpeedLevel speedLevel) {
    if (MovingComponent::initWithAgent(agent, speedLevel)) {
        curWP = 0;

        return true;
    }
    return false;
}


void WayPointMovingComponent::update(float dt) {
    m_uTargetPosition = GameModel::instance()->getWayPointForKey(curWP);
    
    if (m_uTargetPosition.x == -1 && m_uTargetPosition.y == -1) {
        MessageDispatcher::instance()->dispatchMessage(0, m_pAgent->getID(), m_pAgent, kMessageReachGoal, NULL);
        return ;
    }
    
    double distSQ = ccpDistanceSQ(m_uTargetPosition, m_pAgent->getPosition());
    if (distSQ < 10) {
        m_uTargetPosition = GameModel::instance()->getWayPointForKey(++curWP);
    }
    
    MovingComponent::update(dt);
}