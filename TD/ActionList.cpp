//
//  ActionList.cpp
//  TD
//
//  Created by Yifeng Wu on 25/01/13.
//
//

#include "ActionList.h"

USING_NS_CC;


ActionList::~ActionList() {
    CC_SAFE_RELEASE_NULL(m_pActions);
}


bool ActionList::init() {
    m_pActions = CCArray::create();
    m_pActions->retain();
    
    return true;
}


void ActionList::update(float dt) {
    for (int i=0; i<m_pActions->count(); i++) {
        Action *action = (Action *)m_pActions->objectAtIndex(i);

        if (action->getBlocking()) {    // block following actions
            return ;
        }
    }
}


void ActionList::pushAction(Action *action, ActionTypes actionKey) {
    m_pActions->addObject(action);
    m_pActionsMap->setObject(action, actionKey);
}


void ActionList::removeAction(ActionTypes actionKey) {
    Action *action = (Action *)m_pActionsMap->objectForKey(actionKey);
    m_pActions->removeObject(action);
    m_pActionsMap->removeObjectForKey(actionKey);
}