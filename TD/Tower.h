//
//  Tower.h
//  TD
//
//  Created by Yifeng Wu on 30/12/12.
//
//

#ifndef __TD__Tower__
#define __TD__Tower__

#include <iostream>
#include "BaseGameEntity.h"
#include "StateMachine.h"
#include "Architecture.h"
#include "ShootingComponent.h"



class Tower : public BaseGameEntity {    
    // weak reference
    CC_PROPERTY(Architecture *, m_pArchitecture, Architecture);
    
    AW_GET_COMPONENT(ShootingComponent);
public:
    //
    // Construction && Deconstruction
    //
    virtual ~Tower();
    
    static Tower *create(TowerType type, ControllerType controller);
    
    bool initWithType(TowerType type, ControllerType controller);
    
    
    //
    // From BaseGameEntity
    //    
    virtual bool handleMessage(const Telegram *telegram);
        
    virtual double getCollisionRadius() const;
    
    //
    // For Testing
    //
    void popMenu();
    
    void changeState(State<Tower> *newState);
    
    void upgrade(CCObject *sender);
    
    
    void displayInfo(CCObject *sender);
    
    void displayUpgradeInfo(CCObject *sender);
    
    void update(float dt);
};

#endif /* defined(__TD__Tower__) */
