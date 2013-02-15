//
//  Tower.cpp
//  TD
//
//  Created by Yifeng Wu on 30/12/12.
//
//

#include "Tower.h"
#include "TowerStateIdle.h"
#include "TowerGlobalState.h"
#include "GameModel.h"
#include "AWArray.h"

USING_NS_CC;

//--------------------------------
// Construction && Deconstruction - BEGIN
//--------------------------------

#define kTowerDescriptionTag         111

Tower::~Tower() {

}


Tower *Tower::create(TowerType type, ControllerType controller) {
    Tower *tower = new Tower();
    if (tower && tower->initWithType(type, controller)) {
        tower->autorelease();
        return tower;
    }
    CC_SAFE_DELETE(tower);
    return tower;
}


bool Tower::initWithType(TowerType type, ControllerType controller) {
    if (BaseGameEntity::initWithControllerType(controller)) {
        
        // Architecture
        //-------------------
        m_pArchitecture = Architecture::getArchitectureForType(type);
        
        // Set Sprite
        //-------------------
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pArchitecture->getSpriteName());
        m_pSprite->setDisplayFrame(frame);
        GameModel::instance()->getBatch()->addChild(m_pSprite);
        
        // Shooting Component
        //-------------------
        m_pComponents->setObject(ShootingComponent::create(this), kShootingComponent);
        
        // Touch Component
        //-------------------
        m_pComponents->setObject(TouchComponent::create(this, 1, this, menu_selector(Tower::popMenu), m_pArchitecture->getBodyRadius()), kTouchComponent);
        
        // State Machine Component
        //-------------------
        StateMachine<Tower> *pSM = StateMachine<Tower>::create(this);
        pSM->setGlobalState(TowerGlobalState::instance());
        pSM->changeState(TowerStateIdle::instance());
        m_pComponents->setObject(pSM, kStateMachineComponent);
        
        // Collision Component
        //-------------------
        getCollisionComponent()->setQueryRadius(m_pArchitecture->getGuardingRadius());
        getCollisionComponent()->setCollisionRadius(m_pArchitecture->getGuardingRadius());
        
        // Set entity type
        //-------------------
        m_eEntityType = kTower;
        
        return true;
    }
    return false;
}
// END


// -----------------------------
// From BaseGameEntity - BEGIN
// -----------------------------

bool Tower::handleMessage(const Telegram *telegram) {
//    return m_pStateMachine->handleMessage(telegram);
    return ((StateMachine<Tower> *)getComponent(kStateMachineComponent))->handleMessage(telegram);
}


double Tower::getCollisionRadius() const {
    return 50;
}


void Tower::update(float dt) {
    // 1. Set the correct targets - remove old targets
    /*
    CCArray *targetsToBeRemoved = CCArray::create();
    for (int i=0; i<m_pTargets->count(); i++) {
        CCObject *targetObj = m_pTargets->objectAtIndex(i);
        if (!m_pEntitiesCollided->containsObject(targetObj)) {
            targetsToBeRemoved->addObject(targetObj);
        }
    }
    m_pTargets->removeObjectsInArray(targetsToBeRemoved);
     */
    AWArray targetsToBeRemoved;
    for (int i=0; i<m_pTargets->size(); i++) {
        int oldTarget = m_pTargets->getDataAtIndex(i);
        // Old target in targets is not collided recently, meaning out of range
        if (!getCollisionComponent()->getEntitiesCollied()->contains(oldTarget)) {
            targetsToBeRemoved.push(oldTarget);
        }
    }
    m_pTargets->removeDataFromArray(targetsToBeRemoved);
    
    
    // 2. Update
    //m_pStateMachine->update(dt);
    ((StateMachine<Tower> *)getComponent(kStateMachineComponent))->update(dt);
    
    // 3. Cleans the collided objects
    getCollisionComponent()->getEntitiesCollied()->removeAllData();
    
}


//
// For Testing
//
void Tower::popMenu() {
    PopupMenu *menu = GameModel::instance()->getPopupMenu();
    
    menu->displayMenuAt(m_uPosition);
    
    std::vector<TowerType> *vec =m_pArchitecture->getUpgradables();
    for (int i=0; i<vec->size(); i++) {
        Architecture *upgrade = Architecture::getArchitectureForType((*vec)[i]);
        
        // Menu item location
        MenuItemLocation loc;
        if (vec->size() == 1) {
            loc = kTopMid;
        }
        else {
            if (i == 0) {
                loc = kTopLeft;
            }
            if (i == 1) {
                loc = kTopRight;
            }
        }
        
        menu->setChoice(upgrade->getName(), this, menu_selector(Tower::displayUpgradeInfo), loc, upgrade->getType());
    }
}


void Tower::upgrade(CCObject *sender) {
    if (sender) {
        CCMenuItem *item = (CCMenuItem *)sender;
        
        TowerType type = (TowerType)item->getTag();
        setArchitecture(Architecture::getArchitectureForType(type));
        
        GameModel::instance()->getPopupMenu()->closeMenu();
        GameModel::instance()->getGamePlayScene()->removeChildByTag(kTowerDescriptionTag, true);
    }
}

void Tower::displayInfo(CCObject *sender) {
    CCLog("---Name: %s", m_pArchitecture->getName());
    CCLog("---Sprite Name: %s", m_pArchitecture->getSpriteName());
    CCLog("---Resource Needed: %d", m_pArchitecture->getResourceNeeded());
    CCLog("---Upgradables: %d", m_pArchitecture->getUpgradables()->front());
}


void Tower::displayUpgradeInfo(CCObject *sender) {
    if (sender) {
        CCMenuItemLabel *item = (CCMenuItemLabel *)sender;
        CCLabelTTF *confirmLabel = CCLabelTTF::create("Y", "Arial", 20);
        item->setLabel(confirmLabel);
        item->setTarget(this, menu_selector(Tower::upgrade));
    }
    
    Architecture * upgrade = Architecture::getArchitectureForType(m_pArchitecture->getUpgradables()->front());
    CCLabelTTF *description = CCLabelTTF::create(upgrade->getDescription(), "Arial", 10);
    CCPoint pos = getPosition();
    pos.y += 60;

    description->setPosition(pos);
    
    GameModel::instance()->getGamePlayScene()->addChild(description, 10, kTowerDescriptionTag);
}


void Tower::changeState(State<Tower> *newState) {
    ((StateMachine<Tower> *)getComponent(kStateMachineComponent))->changeState(newState);
}


//--------------------------------
// Getters && Setters
//--------------------------------
Architecture *Tower::getArchitecture() {
    return m_pArchitecture;
}

void Tower::setArchitecture(Architecture *var) {
    m_pArchitecture = var;
    
    // sprite
    CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_pArchitecture->getSpriteName());
    m_pSprite->setDisplayFrame(frame);
    
    // collision
    getCollisionComponent()->setQueryRadius(m_pArchitecture->getGuardingRadius());
    getCollisionComponent()->setCollisionRadius(m_pArchitecture->getGuardingRadius());
    
}