//
//  CollisionComponent.cpp
//  TD
//
//  Created by Yifeng Wu on 16/01/13.
//
//

#include "CollisionComponent.h"
#include "BaseGameEntity.h"
#include "CollisionManager.h"
#include "MessageDispatcher.h"

USING_NS_CC;

// Construction && Deconstruction
//-----------------------------------

CollisionComponent::~CollisionComponent() {
    CC_SAFE_DELETE(m_pEntitiesCollided);
}


CollisionComponent *CollisionComponent::create(BaseGameEntity *agent, double queryR, double collisionR) {
    CollisionComponent *retval = new CollisionComponent();
    if (retval && retval->init(agent, queryR, collisionR)) {
        retval->autorelease();
        return retval;
    }
    CC_SAFE_DELETE(retval);
    return NULL;
}


bool CollisionComponent::init(BaseGameEntity *agent, double queryR, double collisionR) {
    m_pAgent = agent;
    m_eType = kCollisionComponent;
    
    m_dQueryRadius = queryR;
    m_dCollisionRadius = collisionR;
    m_bIsActive = true;
    
    m_pEntitiesCollided = new AWArray();
    
    // register with touch manager
    CollisionManager::instance()->registerEntity(this);
    
    return true;
}


void CollisionComponent::clean() {
    CollisionManager::instance()->removeEntity(this);
}


// Logics
//-----------------------------------

const CCPoint &CollisionComponent::getOldPosition() const {
    return m_pAgent->getOldPosition();
}

const CCPoint &CollisionComponent::getPosition() const {
    return m_pAgent->getPosition();
}

void CollisionComponent::collideWith(int colliderID) {
    MessageDispatcher::instance()->dispatchMessage(0, colliderID, m_pAgent, kMessageCollide, NULL);
    m_pEntitiesCollided->push(colliderID);
}

unsigned int CollisionComponent::getID() const {
return m_pAgent->getID();
}
