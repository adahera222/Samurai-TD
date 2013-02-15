//
//  TouchComponent.h
//  TD
//
//  Created by Yifeng Wu on 27/12/12.
//
//

#ifndef __TD__TouchComponent__
#define __TD__TouchComponent__

#include <iostream>
#include "cocos2d.h"
#include "ComponentBase.h"


class BaseGameEntity;

class TouchComponent : public cocos2d::CCTouchDelegate, public ComponentBase {
    
// handle touch events
//---------------------------
    cocos2d::CCObject *m_pListener;
    cocos2d::SEL_MenuHandler m_pfnSelector;
    
    bool isTouchInside(cocos2d::CCTouch *pTouch);
    
    CC_SYNTHESIZE(double, m_dRadius, Radius);
    
// From TouchDelegate
//---------------------------
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
public:
// Construction && Deconstruction
//---------------------------------    
    // the smaller the int, the higher the priority
    static TouchComponent *create(BaseGameEntity *agent, int priority, cocos2d::CCObject *listener, cocos2d::SEL_MenuHandler selctor, double radius);
    static TouchComponent *create(BaseGameEntity *agent, int priority);
    
    bool init(BaseGameEntity *agent, int priority, cocos2d::CCObject *listener, cocos2d::SEL_MenuHandler selctor, double radius);
    
    void clean();
    
    void setSelectorWithTarget(cocos2d::CCObject *listener, cocos2d::SEL_MenuHandler selector);
};

#endif /* defined(__TD__TouchComponent__) */
