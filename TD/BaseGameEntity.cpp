//
//  BaseGameEntity.cpp
//  TD
//
//  Created by Yifeng Wu on 25/12/12.
//
//

#include "BaseGameEntity.h"
#include "GameModel.h"
#include "CollisionManager.h"

USING_NS_CC;

// should be reset to 0
static int sm_uNextValidID = 0;

//
// Construction && Deconstruction - BEGIN
//

BaseGameEntity::~BaseGameEntity() {
    
    // Clean Sprite
    CCSpriteBatchNode *batch = m_pSprite->getBatchNode();
    if (batch) {
        batch->removeChild(m_pSprite, true);
    }
    CC_SAFE_RELEASE_NULL(m_pSprite);
    
    // Clean targets
    CC_SAFE_DELETE(m_pTargets);
    
    // Clean Components
    CCArray *componentKeys = m_pComponents->allKeys();
    for (int i=0; i<componentKeys->count(); i++) {
        int key = ((CCInteger *)componentKeys->objectAtIndex(i))->getValue();
        ComponentBase *component = (ComponentBase *)m_pComponents->objectForKey(key);
        component->clean();
    }
    CC_SAFE_RELEASE_NULL(m_pComponents);
    
    CCLog("--- removed");
}


void BaseGameEntity::release() {
    CCObject::release();
}


bool BaseGameEntity::initWithControllerType(ControllerType controller) {
    m_eController = controller;
    
    // Sprite
    //------------------------
    m_pSprite = CCSprite::create();
    m_pSprite->retain();
    
    // Targets
    //------------------------
    /*
    m_pTargets = CCArray::create();
    m_pTargets->retain();
    m_pEntitiesCollided = CCArray::create();
    m_pEntitiesCollided->retain();
    */
    m_pTargets = new AWArray();
    
    m_uID = sm_uNextValidID++;
    
    // add this to entity manager
    //GameModel::instance()->registerEntity(this);
    
    // v0.21
    // Components Dictionary
    //------------------------
    m_pComponents = CCDictionary::create();
    m_pComponents->retain();
    
    // Collision Component
    //------------------------
    m_pComponents->setObject(CollisionComponent::create(this, 0, 0), kCollisionComponent);
    
    setIsActive(true);
    
    return true;
}
// END


void BaseGameEntity::setPosition(const CCPoint &position) {
    m_uOldPosition = m_uPosition;
    m_uPosition = position;
    
    m_pSprite->setPosition(m_uPosition);
}

void BaseGameEntity::setPosition(float x, float y) {    
    CCPoint pos = ccp(x, y);
    setPosition(pos);
}

const CCPoint &BaseGameEntity::getPosition() const {
    return m_uPosition;
}


void BaseGameEntity::setIsActive(bool var) {
    m_bIsActive = var;
    getCollisionComponent()->setIsActive(var);
}


bool BaseGameEntity::getIsActive() const {
    return m_bIsActive;
}


unsigned int BaseGameEntity::getID() const {
    return m_uID;
}



CCObject *BaseGameEntity::getComponent  (ComponentTypes type) {
    return m_pComponents->objectForKey(type);
}
