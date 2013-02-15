//
//  Figher.cpp
//  TD
//
//  Created by Yifeng Wu on 25/12/12.
//
//

#include "Figher.h"
#include "GameModel.h"
#include "FighterStates.h"
#include "MessageDispatcher.h"


// Construction && Deconstruction - BEGIN
//-----------------------------------------

USING_NS_CC;

Fighter::~Fighter() {
    if (m_pKillers) {
        for (int i=0; i<m_pKillers->size(); i++) {
            MessageDispatcher::instance()->dispatchMessage(0, m_uID, m_pKillers->getDataAtIndex(i), kMessageIAmDying, NULL);
        }
    }
    
    CC_SAFE_DELETE(m_pKillers);
}


Fighter *Fighter::create(FighterType type, ControllerType controller) {
    Fighter *fighter = new Fighter();
    if (fighter && fighter->initWithType(type, controller)) {
        fighter->autorelease();
        return fighter;
    }
    CCLOG("--- Note: cannot create new fighter");
    CC_SAFE_DELETE(fighter);
    return NULL;
}


bool Fighter::initWithType(FighterType type, ControllerType controller) {
    if (!BaseGameEntity::initWithControllerType(controller)) {
        CCLOG("--- Note: cannot initialize BaseGameEntity");
        return false;
    }
    
    // Breed
    //----------------------
    m_pBreed = Breed::getBreedForType(type);
    
    // set sprite
    //----------------------
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pBreed->getSpriteName());
    m_pSprite->setDisplayFrame(frame);
    GameModel::instance()->getBatch()->addChild(m_pSprite);
    
    // Action List
    //----------------------
    /*
    m_pActionList = ActionList::create();
    m_pActionList->retain();
    
    m_pActionList->pushAction(MoveAction::create(this, m_uPosition, 0.3, true), kMoveAction);
    */
    
    // Instance Dependent Attributes
    m_iCurrentHealth = m_pBreed->getMaxHealth();
    
    // Touch Component
    //----------------------
    m_pComponents->setObject(TouchComponent::create(this, 1, this, menu_selector(Fighter::displayInfo), m_pBreed->getBodyRadius()), kTouchComponent);
    
    // State Machine Component
    //----------------------
    m_pStateMachine = StateMachine<Fighter>::create(this, FighterGlobalState::instance(), NULL);
    m_pComponents->setObject(m_pStateMachine, kStateMachineComponent);
    if (m_eController == kNPC) {
        m_pStateMachine->changeState(FighterStateWalking::instance());
    }
    else {
    }
    
    // moving Component
    //----------------------
    if (m_eController == kNPC) {
        m_pComponents->setObject(WayPointMovingComponent::create(this, (SpeedLevel)m_pBreed->getSpeedLevel()), kMovingComponent);
    }
    else {
    m_pComponents->setObject(MovingComponent::create(this, (SpeedLevel)m_pBreed->getSpeedLevel()), kMovingComponent);
    }
    
    // Collision Component
    //----------------------
    getCollisionComponent()->setQueryRadius(m_pBreed->getGuardingRadius());
    getCollisionComponent()->setCollisionRadius(m_pBreed->getBodyRadius());
    
    
    // Killers
    //----------------------
    m_pKillers = new AWArray();
    
    
    // Set entity type
    //----------------------
    m_eEntityType = kFighter;
    
    return true;
}
// END


// From BaseGameEntity - BEGIN
// -----------------------------


bool Fighter::handleMessage(const Telegram *telegram) {
    return m_pStateMachine->handleMessage(telegram);
}

//
// Logics
//
void Fighter::calculateDamage(int damage) {
    m_iCurrentHealth -= damage;
}


void Fighter::displayInfo() {
    CCLog("---Name: %s", m_pBreed->getName());
    CCLog("---Controller: %d", m_eController);
    CCLog("---Entity Type: %d", m_eEntityType);
    CCLog("---Health: %d / %d", m_iCurrentHealth, m_pBreed->getMaxHealth());

    CCLog("---- Retain Count: %d", m_uReference);
}

void Fighter::update(float dt) {
    m_pStateMachine->update(dt);
    //m_pActionList->update(dt);
}
// END