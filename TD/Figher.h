//
//  Figher.h
//  TD
//
//  Created by Yifeng Wu on 25/12/12.
//
//

#ifndef __TD__Figher__
#define __TD__Figher__

#include <iostream>
#include "BaseGameEntity.h"
#include "StateMachine.h"
#include "Breed.h"
#include "MovingComponent.h"
#include "WayPointMovingComponent.h"
#include "ActionList.h"
#include "MoveAction.h"


/**
 @brief This class is the basic moving units.
 
 It inherits from BaseGameEntity class.
 
 It has the following features:
    1. state machine
    2. moving component
    3. breed
 
 */
class Fighter : public BaseGameEntity {
    CC_SYNTHESIZE_READONLY(StateMachine<Fighter> *, m_pStateMachine, StateMachine);     // weak reference
    
    CC_SYNTHESIZE(Breed *, m_pBreed, Breed);    // weak reference
        
    cocos2d::CCPoint m_uOldPosition;
    
    //CC_SYNTHESIZE_READONLY(cocos2d::CCArray *, m_pEntitiesKillingMe, EntitiesKillingMe);
    CC_SYNTHESIZE_READONLY(AWArray *, m_pKillers, Killers);
    
    CC_SYNTHESIZE_READONLY(ActionList *, m_pActionList, ActionList);
    
    
public:
    // Construction && Deconstruction
    //--------------------------------
    virtual ~Fighter();
        
    static Fighter *create(FighterType type, ControllerType controller);
    
    virtual bool initWithType(FighterType type, ControllerType controller);
    
    // Instance Dependent Attributes
    //--------------------------------
    CC_SYNTHESIZE(int, m_iCurrentHealth, CurrentHealth);
    
    
    // From BaseGameEntity
    //--------------------------------
    virtual bool handleMessage(const Telegram *telegram);
            
    //virtual double getCollisionRadius() const;

    // Logics
    //--------------------------------
    AW_GET_COMPONENT(MovingComponent);
    
    void calculateDamage(int damage);
    
    virtual void displayInfo();
    
    virtual void update(float dt);

};

#endif /* defined(__TD__Figher__) */
