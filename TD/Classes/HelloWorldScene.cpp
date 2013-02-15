#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "CollisionManager.h"
#include "MessageDispatcher.h"


#include "Figher.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    CCScene *scene = CCScene::create();
    
    HelloWorld *layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}


bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("test2.plist");
    m_pBatch = CCSpriteBatchNode::create("test2.png");
    this->addChild(m_pBatch);
    
    setTarget(Fighter::create(kPeasant, kNPC));
    m_pTarget->setPosition(100, 200);
        
    scheduleUpdate();
    
    setTouchEnabled(true);
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


//
// Testing
//

void HelloWorld::setTarget(BaseGameEntity *target) {
    CC_SAFE_RELEASE(m_pTarget);
    
    m_pTarget = target;
    
    m_pBatch->addChild(target->getSprite());
}


void HelloWorld::update(float dt) {
    CollisionManager::instance()->update(dt);
}


void HelloWorld::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent) {
    
    // touch
    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    CCLog("---location (%f, %f)", location.x, location.y);
    
    /*
    // Test Messaging
    MessageDispatcher::instance()->dispatchMessage(0, 0, 0, kTesting, (void *)"Hello World");
     */
    
    /*
    // Test Collision
    Fighter *newFighter = Fighter::create(kPeasant);
    m_pBatch->addChild(newFighter->getSprite());
    
    newFighter->setPosition(location);
     */
}