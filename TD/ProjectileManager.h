//
//  ProjectileManager.h
//  TD
//
//  Created by Yifeng Wu on 07/01/13.
//
//

#ifndef __TD__ProjectileManager__
#define __TD__ProjectileManager__

#include <iostream>
#include "cocos2d.h"
#include "Projectile.h"

class ProjectileManager : public cocos2d::CCObject {
    cocos2d::CCArray *m_pProjectiles;
    
    cocos2d::CCDictionary *m_pProjectileModels;
    
    int m_iNextValidID;
    
    int m_iTotalProjectiles;
    
    CC_SYNTHESIZE(bool, m_bAllowProjectile, AllowProjectile);
    
public:
    ~ProjectileManager();

    CREATE_FUNC(ProjectileManager);

    bool init();

    Projectile *getProjectile(ProjectileTypes type, const cocos2d::CCPoint &targetPos, const cocos2d::CCPoint &originPos, ControllerType controller);
};

#endif /* defined(__TD__ProjectileManager__) */
