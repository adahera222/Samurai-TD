//
//  MapTouchLayer.h
//  TD
//
//  Created by Yifeng Wu on 29/12/12.
//
//

#ifndef __TD__MapTouchLayer__
#define __TD__MapTouchLayer__

#include <iostream>
#include "cocos2d.h"

class MapTouchLayer : public cocos2d::CCLayer {
    // holds the game's visual representation
    cocos2d::CCNode *m_pGameMap;    // weak reference
    
    cocos2d::CCPoint m_uCurPos;     // gl
    cocos2d::CCPoint m_uPrevPos;    // gl
    
    void registerWithTouchDispatcher();
    

public:
    ~MapTouchLayer();
    
    static MapTouchLayer *create(cocos2d::CCNode *gameMap);
    
    bool initWithGameMap(cocos2d::CCNode *gameMap);
    
    //
    // Human Interaction
    //
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

#endif /* defined(__TD__MapTouchLayer__) */
