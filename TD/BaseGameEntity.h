//
//  BaseGameEntity.h
//  TD
//
//  Created by Yifeng Wu on 25/12/12.
//
//

#ifndef __TD__BaseGameEntity__
#define __TD__BaseGameEntity__

#include <iostream>
#include "cocos2d.h"
#include "Telegram.h"
#include "TouchComponent.h"
#include "ComponentBase.h"
#include "CollisionComponent.h"
#include "AWArray.h"


#define AW_GET_COMPONENT(componentClass)\
public: virtual componentClass *get##componentClass(void) const { return (componentClass *)m_pComponents->objectForKey(k##componentClass); }


#define AW_GET_COMPONENT_FROM(varName, componentClass)\
varName->get##componentClass()


enum ControllerType {
    kNoController = 0,
    kPlayer = 1,
    kNPC = 2,
    };


enum EntityTypes {
    kUnknownEntityType = 0,
    kFighter = 1,
    kTower = 2,
    kProjectile = 3,
    };


/**
 * It is the base class for the game entities.
 
 * It provides the following features:
        - visual representation (Sprite)
        - position
        - collision detection
        - targets
        - components
        - and more

 * It is recommended to inherit game entities from this class.
 */
class BaseGameEntity : public cocos2d::CCObject {
    
protected:

// Attributes
//--------------
    CC_SYNTHESIZE(cocos2d::CCSprite *, m_pSprite, Sprite);
        
    cocos2d::CCPoint m_uPosition;
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(cocos2d::CCPoint, m_uOldPosition, OldPosition);
    
    CC_SYNTHESIZE(ControllerType, m_eController, Controller);
    
    CC_SYNTHESIZE(AWArray *, m_pTargets, Targets);
    
    // You can add various component to Components, such as touch component & .
    CC_SYNTHESIZE_READONLY(cocos2d::CCDictionary *, m_pComponents, Components);
    
    bool m_bIsActive;
    
    CC_SYNTHESIZE_READONLY(EntityTypes, m_eEntityType, EntityType);
    
    
public:

// Construction && Deconstruction
//--------------------------------
    virtual ~BaseGameEntity();
    
    /*
     @override
     */
    void release();
    
    // initialize the entity, the entity will be added to entity manager.
    bool initWithControllerType(ControllerType controller);
    
    
    virtual void setPosition(const cocos2d::CCPoint &position);
    virtual void setPosition(float x, float y);
    const cocos2d::CCPoint &getPosition() const;
    
    virtual void setIsActive(bool var);
    virtual bool getIsActive() const;
    
    unsigned int getID() const;
    
    CCObject *getComponent(ComponentTypes type);
    AW_GET_COMPONENT(CollisionComponent);
    AW_GET_COMPONENT(TouchComponent);


// Interfaces
//--------------------------------
    // for messaging handling
    virtual bool handleMessage(const Telegram *telegram) = 0;
    
    virtual void update(float dt) = 0;
    
};

#endif /* defined(__TD__BaseGameEntity__) */
