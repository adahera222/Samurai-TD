//
//  BaseEntity.h
//  TD
//
//  Created by Yifeng Wu on 26/01/13.
//
//

#ifndef __TD__BaseEntity__
#define __TD__BaseEntity__

#include <iostream>
#include "cocos2d.h"
#include "ActionList.h"

/**
 * This class is the base class for entities in the game.
 
 * It can be viewed as a container for components which actually provide functionalities, and a container for actions which utilizes the comonents to do real works.
 
 */
class BaseEntity : public cocos2d::CCObject {
    
    /**
     * A container for components.
     */
    CC_SYNTHESIZE_READONLY(cocos2d::CCDictionary *, m_pComponents, Components);
    
    
    CC_SYNTHESIZE_READONLY(bool, m_bActive, Active);
    
    /** 
     * The bits to show what components does the entity equip.
     * e.g. 0001 may be the Sprite Component.
     */
    CC_SYNTHESIZE(unsigned long, m_Equipped, Equipped);
    
    /**
     * A container for actions.
     */
    CC_SYNTHESIZE_READONLY(ActionList *, m_pActionList, ActionList);
    
public:
    // Construction && Deconstruction
    //------------------------------------
    virtual ~BaseEntity();
    
    static BaseEntity *createWithFile(const char *file);
    
    bool initWithFile(const char *file);
    
    // Getters && Setters
    //------------------------------------
    unsigned int getID() const;
    
    //virtual bool handleMessage()
    
    virtual void update(float dt);
};

#endif /* defined(__TD__BaseEntity__) */
