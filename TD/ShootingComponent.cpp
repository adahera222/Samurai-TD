//
//  ShootingComponent.cpp
//  TD
//
//  Created by Yifeng Wu on 06/01/13.
//
//

#include "ShootingComponent.h"
#include "BaseGameEntity.h"
#include "GameModel.h"
#include "Tower.h"

USING_NS_CC;

// Construction && Deconstruction
//-----------------------------------

ShootingComponent *ShootingComponent::create(BaseGameEntity *agent) {
    ShootingComponent *retVal = new ShootingComponent();
    if (retVal && retVal->init(agent)) {
        retVal->autorelease();
        return retVal;
    }
    CC_SAFE_DELETE(retVal);
    return NULL;
}


bool ShootingComponent::init(BaseGameEntity *agent) {
    m_pAgent = agent;
    m_eType = kShootingComponent;

    m_fTimePassed = 0;
    
    return true;
}


// Logics
//-----------------------------------

void ShootingComponent::shoot(float dt, ProjectileTypes projectileType, float interval) {
    m_fTimePassed += dt;
    
    if (m_fTimePassed >= interval) {
        //BaseGameEntity *target = (BaseGameEntity *)m_pAgent->getTargets()->objectAtIndex(0);
        //CCLog("---Shoot at: %d", target->getID());
        
        int targetID = m_pAgent->getTargets()->getDataAtIndex(0);
        BaseGameEntity *target = GameModel::instance()->getEntityForID(targetID);
        
        (Projectile *)GameModel::instance()->getProjectileManager()->getProjectile(projectileType, target->getPosition(), m_pAgent->getPosition(), m_pAgent->getController());
        
        //CCLog("--- projectile: %d", proj->getID());
        m_fTimePassed = 0;
    }
}