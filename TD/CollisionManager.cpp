//
//  CollisionManager.cpp
//  TD
//
//  Created by Yifeng Wu on 25/12/12.
//
//

#include "CollisionManager.h"
//#include "BaseGameEntity.h"
#include "MessageDispatcher.h"
#include "CollisionComponent.h"

USING_NS_CC;

static CollisionManager *sg_pSharedCollisionManager;

//
// Construction && Deconstruction - BEGIN
//

CollisionManager::~CollisionManager() {
    CC_SAFE_RELEASE(m_pPartition);
    
    CC_SAFE_RELEASE(m_pEntities);
}


void CollisionManager::purge() {
    CC_SAFE_RELEASE_NULL(sg_pSharedCollisionManager);
}


bool CollisionManager::init() {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize(); // need to be updated
    CCLog("---win size: x:%f, y:%f", winSize.width, winSize.height);
    m_pPartition = CellSpacePartition::create(winSize, 7, 7, 20);
    m_pPartition->retain();
    
    m_pEntities = CCArray::create();
    m_pEntities->retain();

    return true;
}


CollisionManager *CollisionManager::instance() {
    if (!sg_pSharedCollisionManager) {
        sg_pSharedCollisionManager = new CollisionManager();
        sg_pSharedCollisionManager->init();
    }
    
    return sg_pSharedCollisionManager;
}
// END


//
// Functions
//

void CollisionManager::registerEntity(CollisionComponent *entity) {
    m_pPartition->addEntity(entity);
    m_pEntities->addObject(entity);
}


void CollisionManager::removeEntity(CollisionComponent *entity) {
    m_pPartition->removeEntity(entity);
    m_pEntities->removeObject(entity);
}


void CollisionManager::update(float dt) {
    CC_UNUSED_PARAM(dt);
    
    // update entities' cell location
    for (int i=0; i<m_pEntities->count(); i++) {
        CollisionComponent *entity = (CollisionComponent *)m_pEntities->objectAtIndex(i);
                
        if (entity->getIsActive()) {
            m_pPartition->updateEntity(entity, entity->getOldPosition());
        }
    }
    
    // test collision & send messages to collided ones
    for (int i=0; i<m_pEntities->count(); i++) {    // every entity
        CollisionComponent *entity = (CollisionComponent *)m_pEntities->objectAtIndex(i);
        
        if (!entity->getIsActive()) {
            continue;
        }

        m_pPartition->calculateNeighbours(entity, entity->getQueryRadius(), entity->getCollisionRadius());

        //m_pPartition->calculateNeighbours(entity, entity->getCollisionRadius());
        
        CCArray *neighbours = m_pPartition->getNeighbours();

        for (int j=0; j<neighbours->count(); j++) {     // every neighbour of entity
            CollisionComponent *neighbour = (CollisionComponent *)neighbours->objectAtIndex(j);
            
            if (!neighbour->getIsActive()) {
                continue;
            }
            
            // If the neighbour comes into the entity's collision area, we should let the entity know, therefore, the entity should be the receiver and neighbour should be the sender.
            //MessageDispatcher::instance()->dispatchMessage(0, neighbour->getID(), entity->getID(), kMessageCollide, (void *)"Hi we collide!");
            entity->collideWith(neighbour->getID());
        }
    }
}