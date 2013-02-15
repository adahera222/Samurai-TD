//
//  EntityManager.cpp
//  TD
//
//  Created by Yifeng Wu on 26/12/12.
//
//

#include "EntityManager.h"
#include "BaseGameEntity.h"

USING_NS_CC;

//
// Construction && Deconstruction - BEGIN
//

EntityManager::~EntityManager() {
    CC_SAFE_RELEASE(m_pIDToEntitiesMap);
    //CC_SAFE_RELEASE(m_pEntitiesToAdd);
    CC_SAFE_RELEASE(m_pEntitiesToRemove);
}


EntityManager *EntityManager::create() {
    static bool inited = false;
    CCAssert(inited == false, "---EntityManager has benn inited already !");
    
    inited = true;
    
    EntityManager *em = new EntityManager();
    if (em && em->init()) {
        em->autorelease();
        return em;
    }
    CC_SAFE_DELETE(em);
    return NULL;
}


bool EntityManager::init() {
    m_pIDToEntitiesMap = CCDictionary::create();
    m_pIDToEntitiesMap->retain();
    /*
    m_pEntitiesToAdd = CCArray::create();
    m_pEntitiesToAdd->retain();
    */
    m_pEntitiesToRemove = CCArray::create();
    m_pEntitiesToRemove->retain();
    
    return true;
}
// END

//
// Functions - BEGIN
//

void EntityManager::registerEntity(BaseGameEntity *entity) {
    int id = entity->getID();
    m_pIDToEntitiesMap->setObject(entity, id);
    //m_pEntitiesToAdd->addObject(entity);
}


void EntityManager::removeEntity(BaseGameEntity *entity) {
    //int id = entity->getID();
    //m_pIDToEntitiesMap->removeObjectForKey(id);
    entity->setIsActive(false);
    m_pEntitiesToRemove->addObject(entity);
}


BaseGameEntity *EntityManager::getEntityForID(int ID) const {
    CCObject *obj = m_pIDToEntitiesMap->objectForKey(ID);
    return (BaseGameEntity *)obj;
}
// END


void EntityManager::update(float dt) {
    CCArray *keys = m_pIDToEntitiesMap->allKeys();
    if (keys) {     // if the dictionary has no objects, keys will be NULL
        for (int i=0; i<keys->count(); i++) {
            CCInteger *integer = (CCInteger *)keys->objectAtIndex(i);
            int key = integer->getValue();
            
            BaseGameEntity *entity = (BaseGameEntity *)m_pIDToEntitiesMap->objectForKey(key);
            if (entity->getIsActive()) {    // Only update the entity if it's active.
                entity->update(dt);
            }
        }
    }
    
    /*
    // Add new entities.
    for (int i=0; i<m_pEntitiesToAdd->count(); i++) {
        BaseGameEntity *newEntity = (BaseGameEntity *)m_pEntitiesToAdd->objectAtIndex(i);
        m_pIDToEntitiesMap->setObject(newEntity, newEntity->getID());
    }
    m_pEntitiesToAdd->removeAllObjects();
    */
    
    // Remove old entities.
    for (int i=0; i<m_pEntitiesToRemove->count(); i++) {
        BaseGameEntity *oldEntity = (BaseGameEntity *)m_pEntitiesToRemove->objectAtIndex(i);
        m_pIDToEntitiesMap->removeObjectForKey(oldEntity->getID());
    }
    m_pEntitiesToRemove->removeAllObjects();
}