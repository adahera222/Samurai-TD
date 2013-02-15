#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "BaseGameEntity.h"

class HelloWorld : public cocos2d::CCLayer
{
private:
    BaseGameEntity *m_pTarget;
    
    cocos2d::CCSpriteBatchNode *m_pBatch;
    
public:
    virtual bool init();

    static cocos2d::CCScene* scene();
    
    void menuCloseCallback(CCObject* pSender);

    CREATE_FUNC(HelloWorld);
    
    //
    // Testing
    //
    void setTarget(BaseGameEntity *target);
    
    void update(float dt);

    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
};

#endif // __HELLOWORLD_SCENE_H__
