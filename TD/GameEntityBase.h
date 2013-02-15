//
//  GameEntityBase.h
//  IM-Big-Devil
//
//  Created by Yifeng Wu on 19/12/12.
//
//

#ifndef __IM_Big_Devil__GameEntityBase__
#define __IM_Big_Devil__GameEntityBase__

#include <iostream>
#include "cocos2d.h"
#include "Vector2D.h"

class GameEntityBase : public cocos2d::CCSprite {
    CC_SYNTHESIZE(Vector2D, m_vVelocity, Velocity);
    
    CC_SYNTHESIZE(Vector2D, m_vHeading, Heading);
    
    CC_SYNTHESIZE(Vector2D, m_vSide, Side);
    
public:

};

#endif /* defined(__IM_Big_Devil__GameEntityBase__) */
