//
//  ShootingComponent.h
//  TD
//
//  Created by Yifeng Wu on 06/01/13.
//
//

#ifndef __TD__ShootingComponent__
#define __TD__ShootingComponent__

#include <iostream>
#include "cocos2d.h"
#include "ComponentBase.h"
#include "Projectile.h"


class ShootingComponent : public ComponentBase {
    ProjectileTypes m_eProjectileType;
    CC_SYNTHESIZE(float, m_fInterval, Interval);
    
    float m_fTimePassed;
        
public:

// Construction && Deconstruction
//-----------------------------------
    ~ShootingComponent() {}
    
    static ShootingComponent *create(BaseGameEntity *agent);
    
    bool init(BaseGameEntity *agent);
    
// Logics
//-----------------------------------
    
    //void shoot(float dt);
    void shoot(float dt, ProjectileTypes projectileType, float interval);
};

#endif /* defined(__TD__ShootingComponent__) */
