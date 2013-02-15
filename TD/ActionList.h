//
//  ActionList.h
//  TD
//
//  Created by Yifeng Wu on 25/01/13.
//
//

#ifndef __TD__ActionList__
#define __TD__ActionList__

#include <iostream>
#include "cocos2d.h"
#include "Action.h"


#define AW_GET_ACTION(actionClass)\
public: componentClass *get##actionClass(void) const {return (componentClass *)m_pActionList->getActionForKey(k##actionClass); }


class ActionList : public cocos2d::CCObject {
    CC_SYNTHESIZE_READONLY(cocos2d::CCArray *, m_pActions, Actions);
    CC_SYNTHESIZE_READONLY(cocos2d::CCDictionary *, m_pActionsMap, ActionsMap);
    
public:
    ~ActionList();
    
    CREATE_FUNC(ActionList);
    
    bool init();
    
    void pushAction(Action *action, ActionTypes actionKey);

    void removeAction(ActionTypes actionKey);
    
    Action *getActionForKey(ActionTypes actionKey);
    
    void update(float dt);
};

#endif /* defined(__TD__ActionList__) */
