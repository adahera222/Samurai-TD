//
//  MovingComponent.cpp
//  TD
//
//  Created by Yifeng Wu on 25/12/12.
//
//

#include "MovingComponent.h"
#include "BaseGameEntity.h"
#include "MessageDispatcher.h"

USING_NS_CC;

//
// Construction && Deconstruction - BEGIN
//

MovingComponent::~MovingComponent() {
    
}


MovingComponent *MovingComponent::create(BaseGameEntity *agent, SpeedLevel speedLevel) {
    MovingComponent *component = new MovingComponent();
    if (component && component->initWithAgent(agent, speedLevel)) {
        component->autorelease();
        return component;
    }
    CCLog("--- Note: cannot create moving component");
    CC_SAFE_DELETE(component);
    return NULL;
}


bool MovingComponent::initWithAgent(BaseGameEntity *agent, SpeedLevel speedLevel) {
    m_pAgent = agent;
    
    m_eType = kMovingComponent;

    m_uTargetPosition = agent->getPosition();
    m_eSpeedLevel = speedLevel;
    
    return true;
}
// END


//
// Logics - BEGIN
//
void MovingComponent::update(float dt) {
    CCPoint agentPos = m_pAgent->getPosition();
    
    if (fabsf(agentPos.x - m_uTargetPosition.x) < 2 && fabsf(agentPos.y - m_uTargetPosition.y) < 2) {
        MessageDispatcher::instance()->dispatchMessage(0, m_pAgent->getID(), m_pAgent->getID(), kMessageReachPosition, (void *)&m_uTargetPosition);
        return ;
    }
    
    CCPoint direction = ccpSub(m_uTargetPosition, agentPos);
    CCPoint n = ccpNormalize(direction);
    
    double kSpeedTweaker = 0.2;
    double k = m_eSpeedLevel * kSpeedTweaker;
    n.x *= k;
    n.y *= k;
    
    CCPoint goTo = ccpAdd(m_pAgent->getPosition(), n);
    m_pAgent->setPosition(goTo);
}
// END