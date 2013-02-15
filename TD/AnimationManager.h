//
//  AnimationManager.h
//  TD
//
//  Created by Yifeng Wu on 22/01/13.
//
//

#ifndef __TD__AnimationManager__
#define __TD__AnimationManager__

#include <iostream>
#include "cocos2d.h"   
#include "AWArray.h"

class AnimationManager : public cocos2d::CCObject {
    cocos2d::CCAnimationCache *m_pCache;    // weak reference
    
    
public:
    CREATE_FUNC(AnimationManager);
    
    bool init();

    void addAnimation(cocos2d::CCArray *frames, AWArray *numsOfFrame, float interval, const char *name);
};

#endif /* defined(__TD__AnimationManager__) */
