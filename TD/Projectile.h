//
//  Projectile.h
//  TD
//
//  Created by Yifeng Wu on 07/01/13.
//
//

#ifndef __TD__Projectile__
#define __TD__Projectile__

#include <iostream>
#include "cocos2d.h"
#include "BaseGameEntity.h"
#include "MovingComponent.h"

enum ProjectileTypes {
    kProjectileBullet = 1,
    };


class Projectile : public BaseGameEntity {
    CC_SYNTHESIZE_READONLY(int, m_iDamage, Damage);
    CC_SYNTHESIZE_READONLY(double, m_dCollisionRadius, CollisionRadius);
    CC_SYNTHESIZE(const char *, m_sSpriteName, SpriteName);
    CC_SYNTHESIZE_READONLY(int, m_iProjectileID, ProjectileID);
    CC_SYNTHESIZE(ProjectileTypes, m_eProjectileType, ProjectileType);
    
    void reset();
public:
    // -------------------------------
    // Construction && Deconstruction
    // -------------------------------
    virtual ~Projectile();
    
    // Create a projectile according to a projectile model
    static Projectile *create(int projectileID, Projectile *model);
    
    bool initWithProjectileID(int projectileID, Projectile *model);
    
    // Model
    static Projectile *createModel(ProjectileTypes type);
    
    bool initModelWithType(ProjectileTypes type);
    
    void readDataFromFile(const char *fileName, const char *tableKey);
    
    void build(Projectile *model, const cocos2d::CCPoint &targetPos, const cocos2d::CCPoint &originPos, ControllerType controller);
    
    AW_GET_COMPONENT(MovingComponent);
    
    // -------------------------------
    // From BaseGameEntity
    // -------------------------------
    //virtual double getQueryRadius() const;
    
    //virtual double getCollisionRadius() const;
    
    virtual bool handleMessage(const Telegram *telegram);
    
    virtual void update(float dt);
};

#endif /* defined(__TD__Projectile__) */
