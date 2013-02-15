//
//  FighterStateWalking.cpp
//  TD
//
//  Created by Yifeng Wu on 01/01/13.
//
//

#include "FighterStateWalking.h"
#include "Figher.h"

USING_NS_CC;

static FighterStateWalking *sg_FighterStateWalking;

FighterStateWalking *FighterStateWalking::instance() {
    if (!sg_FighterStateWalking) {
        sg_FighterStateWalking = new FighterStateWalking();
    }
    return sg_FighterStateWalking;
}


void FighterStateWalking::enter(Fighter *boss) {
    CCAnimation *anim = CCAnimationCache::sharedAnimationCache()->animationByName("fighter_1_walk");
    
    if (anim) {
        CCAnimate *animate = CCAnimate::create(anim);
        boss->getSprite()->runAction(CCRepeatForever::create(animate));
    }
}


void FighterStateWalking::execute(Fighter *boss, float dt) {
    boss->getMovingComponent()->update(dt);
}


void FighterStateWalking::exit(Fighter *boss) {
    
}


bool FighterStateWalking::onMessage(Fighter *entity, const Telegram *telegram) {
    return false;
}