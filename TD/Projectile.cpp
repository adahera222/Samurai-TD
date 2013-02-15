//
//  Projectile.cpp
//  TD
//
//  Created by Yifeng Wu on 07/01/13.
//
//

#include "Projectile.h"
#include "AWLuaHelper.h"
#include "CollisionManager.h"
#include "MessageDispatcher.h"
#include "GameModel.h"

USING_NS_CC;

// -------------------------------
// Construction && Deconstruction - BEGIN
// -------------------------------

Projectile::~Projectile() {
    
}


Projectile *Projectile::create(int projectileID, Projectile *model) {
    Projectile *retVal = new Projectile();
    if (retVal && retVal->initWithProjectileID(projectileID, model)) {
        retVal->autorelease();
        return retVal;
    }
    CC_SAFE_DELETE(retVal);
    return NULL;
}


bool Projectile::initWithProjectileID(int projectileID, Projectile *model) {
    if (BaseGameEntity::initWithControllerType(kNoController)) {
        m_bIsActive = false;    // default
        m_iProjectileID = projectileID;
        
        m_iDamage = model->getDamage();
        m_dCollisionRadius = model->getCollisionRadius();
        m_sSpriteName = model->getSpriteName();
        m_eProjectileType = model->getProjectileType();
        
        // Collision
        getCollisionComponent()->setIsActive(false);
        getCollisionComponent()->setCollisionRadius(m_dCollisionRadius);
        getCollisionComponent()->setQueryRadius(m_dCollisionRadius);

        
        // sprite
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_sSpriteName);
        m_pSprite->setDisplayFrame(frame);
        m_pSprite->setVisible(false);
        GameModel::instance()->getBatch()->addChild(m_pSprite, 2);
        
        // Moving Component
        m_pComponents->setObject(MovingComponent::create(this, UltraFast), kMovingComponent);
            
        return true;
    }
    return false;
}


// Model

Projectile *Projectile::createModel(ProjectileTypes type) {
    Projectile *retval = new Projectile();
    if (retval && retval->initModelWithType(type)) {
        retval->autorelease();
        return retval;
    }
    CC_SAFE_DELETE(retval);
    return NULL;
}


bool Projectile::initModelWithType(ProjectileTypes type) {
    if (BaseGameEntity::initWithControllerType(kNoController)) {
        // default
        m_bIsActive = false;
        m_iProjectileID = -1;
        
        m_eProjectileType = type;
        
        // Read Data
        CCString *typeStr = CCString::createWithFormat("projectile_%d", (int)type);
        
        readDataFromFile("projectileInfo.lua", typeStr->getCString());
        
        // Set entity type
        m_eEntityType = kProjectile;
        
        return true;
    }
    return false;
}


void Projectile::readDataFromFile(const char *fileName, const char *tableKey) {
    static bool executed = false;
    if (!executed) {
        awExecuteLuaFile(fileName);
        executed = true;
    }

    CCLuaEngine *pEngine = CCLuaEngine::defaultEngine();
    pEngine->cleanStack();
    
    lua_State *state = pEngine->getLuaState();
    
    awSetLuaTable(state, tableKey);
    
    // Get Attributes
    m_sSpriteName = awGetLuaStringFromTable(state, "sprite_name");

    m_iDamage = awGetLuaIntFromTable(state, "damage");
    
    m_dCollisionRadius = awGetLuaDoubleFromTable(state, "collision_radius");
}


void Projectile::build(Projectile *model, const CCPoint &targetPos, const CCPoint &originPos, ControllerType controller) {
    if (m_eProjectileType != model->getProjectileType()) {
        m_iDamage = model->getDamage();
        m_sSpriteName = model->getSpriteName();
    
        // Set sprite according to the parameters.
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_sSpriteName);
        m_pSprite->setDisplayFrame(frame);
    }
    
    m_bIsActive = true;
    m_pSprite->setVisible(true);
    
    setPosition(originPos);
    
    m_eController = controller;
    
    getMovingComponent()->setTargetPosition(targetPos);
    //CollisionManager::instance()->registerEntity(this);
    getCollisionComponent()->setIsActive(true);
}

// END


void Projectile::reset() {
    m_bIsActive = false;
    m_pSprite->setVisible(false);
    getCollisionComponent()->setIsActive(false);
}


// -------------------------------
// From BaseGameEntity
// -------------------------------

bool Projectile::handleMessage(const Telegram *telegram) {
    switch (telegram->message) {
        case kMessageReachPosition:
            reset();
            return true;
            
        case kMessageCollide:
            BaseGameEntity *entity = GameModel::instance()->getEntityForID(telegram->sender);
            
            if (arc4random()%10 > 3) {
                return false;
            }
            
            if (entity->getEntityType() == kFighter && entity->getController() != m_eController) {
                MessageDispatcher::instance()->dispatchMessage(0, m_uID, entity->getID(), kMessageHit, (void *)&m_iDamage);
                reset();
                return true;
            }
            return false;
    }
    return false;
}

void Projectile::update(float dt) {
    getMovingComponent()->update(dt);
}