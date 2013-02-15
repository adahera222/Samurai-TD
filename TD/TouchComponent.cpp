//
//  TouchComponent.cpp
//  TD
//
//  Created by Yifeng Wu on 27/12/12.
//
//

#include "TouchComponent.h"
#include "BaseGameEntity.h"

USING_NS_CC;



// Construction && Deconstruction
//-----------------------------------

void TouchComponent::clean() {
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


TouchComponent *TouchComponent::create(BaseGameEntity *agent, int priority) {
    return create(agent, priority, NULL, NULL, 0);
}


TouchComponent *TouchComponent::create(BaseGameEntity *agent, int priority, CCObject *listener, SEL_MenuHandler selctor, double radius) {
    TouchComponent *tc = new TouchComponent();
    if (tc && tc->init(agent, priority, listener, selctor, radius)) {
        tc->autorelease();
        return tc;
    }
    CC_SAFE_DELETE(tc);
    return NULL;
}


bool TouchComponent::init(BaseGameEntity *agent, int priority, CCObject *listener, SEL_MenuHandler selctor, double radius) {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, priority, true);
    
    m_pAgent = agent;
    m_eType = kTouchComponent;
    m_pListener = listener;
    m_pfnSelector = selctor;
    m_dRadius = radius;
    
    return true;
}


void TouchComponent::setSelectorWithTarget(CCObject *listener, SEL_MenuHandler selector) {
    m_pListener = listener;
    m_pfnSelector = selector;
}


// Handle Touch
//---------------------------

bool TouchComponent::isTouchInside(CCTouch *pTouch) {
    CCPoint location = pTouch->getLocation();   // GL coord
    
    double distSQ = ccpDistanceSQ(m_pAgent->getPosition(), location);
    if (distSQ < m_dRadius * m_dRadius) {
        return true;
    }
    return false;
}

// From TouchDelegate
//---------------------------

bool TouchComponent::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    return isTouchInside(pTouch);
}


void TouchComponent::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    if (isTouchInside(pTouch)) {
        if (m_pListener && m_pfnSelector) {
            // execute the selector function, and send the agent as the parameter
            (m_pListener->*m_pfnSelector)(m_pAgent);
        }
    }
}
// END