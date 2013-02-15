//
//  AnimationManager.cpp
//  TD
//
//  Created by Yifeng Wu on 22/01/13.
//
//

#include "AnimationManager.h"

USING_NS_CC;


bool AnimationManager::init() {
    m_pCache = CCAnimationCache::sharedAnimationCache();
    CCLog("created");
    return true;
}


void AnimationManager::addAnimation(cocos2d::CCArray *frames, AWArray *numsOfFrame, float interval, const char *name) {
    CCAssert(frames && numsOfFrame, "--- No frames or no nums of frame");
    
    CCArray *animFrames = CCArray::create();
    
    for (int i=0; i<frames->count(); i++) {
        CCSpriteFrame *frame = (CCSpriteFrame *)frames->objectAtIndex(i);
        int num = numsOfFrame->getDataAtIndex(i);
        
        for (int j=0; j<num; j++) { // add a frame multiple times if need
            animFrames->addObject(frame);
        }
    }
    
    CCAnimation *anim = CCAnimation::createWithSpriteFrames(animFrames, 0.1f);

    m_pCache->addAnimation(anim, name);
}