//
//  ProjectileManager.cpp
//  TD
//
//  Created by Yifeng Wu on 07/01/13.
//
//

#include "ProjectileManager.h"
#include "GameModel.h"

USING_NS_CC;


ProjectileManager::~ProjectileManager() {
    CC_SAFE_RELEASE(m_pProjectiles);
    CC_SAFE_RELEASE(m_pProjectileModels);
}


bool ProjectileManager::init() {
    m_iTotalProjectiles = 100;
    m_iNextValidID = 0;
    
    m_bAllowProjectile = false;
    
    // Models
    
    m_pProjectileModels = CCDictionary::create();
    m_pProjectileModels->retain();
    
    Projectile *model = Projectile::createModel(kProjectileBullet);
    m_pProjectileModels->setObject(model, kProjectileBullet);

    // Projectiles
    
    m_pProjectiles = CCArray::create();
    m_pProjectiles->retain();
    
    if (m_bAllowProjectile) {
        for (int i=0; i<m_iTotalProjectiles; i++) {
            Projectile *proj = Projectile::create(i, model);
            m_pProjectiles->addObject(proj);
            GameModel::instance()->registerEntity(proj);
        }
    }
    return true;
}


Projectile *ProjectileManager::getProjectile(ProjectileTypes type, const CCPoint &targetPos, const CCPoint &originPos, ControllerType controller) {
    Projectile *model = (Projectile *)m_pProjectileModels->objectForKey(type);
    
    Projectile *retval = (Projectile *)m_pProjectiles->objectAtIndex(m_iNextValidID);
    
    if (retval->getIsActive()) {
        CCLog("No inactive projectile available");
        return NULL;
    }
    
    retval->build(model, targetPos, originPos, controller);
    
    m_iNextValidID++;
    m_iNextValidID = m_iNextValidID % m_iTotalProjectiles;
    
    return model;
}