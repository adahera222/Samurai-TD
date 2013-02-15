//
//  GamePlayLayer.cpp
//  TD
//
//  Created by Yifeng Wu on 29/12/12.
//
//

#include "GamePlayScene.h"
#include "GameModel.h"
#include "CollisionManager.h"

#include "Figher.h"
#include "Tower.h"

#include "MessageDispatcher.h"

USING_NS_CC;

// ------------------------------
// Construction && Deconstruction - BEGIN
// ------------------------------

GamePlayScene::~GamePlayScene() {
    CC_SAFE_RELEASE_NULL(m_pBatch);
    CC_SAFE_RELEASE_NULL(m_pTouchLayer);
    //CC_SAFE_RELEASE_NULL(m_pMap);
    
    CCSpriteFrameCache::purgeSharedSpriteFrameCache();
    GameModel::purge();
    CollisionManager::purge();
}


CCScene *GamePlayScene::scene() {
    CCScene *scene = CCScene::create();
    GamePlayScene *layer = GamePlayScene::create();
    scene->addChild(layer);
    return scene;
}


bool GamePlayScene::init() {
    if (CCLayer::init()) {
        
        GameModel::configGameModel(this, 0);
        
        /*
        m_pTouchLayer = MapTouchLayer::create(m_pBatch);
        m_pTouchLayer->retain();
        */
        
        /*
        m_pTarget = Fighter::create(kPeasant, kPlayer);
        m_pTarget->retain();
        GameModel::instance()->registerEntity(m_pTarget);
        */
        setTouchEnabled(true);
        
        scheduleUpdate();
        
        return true;
    }
    return false;
}
// END


void GamePlayScene::update(float dt) {
    // collision comes first, which changes the entities' state
    CollisionManager::instance()->update(dt);

    GameModel::instance()->update(dt);
}


// ------------------------------
// Testing
// ------------------------------
/*
void GamePlayScene::setTarget(BaseGameEntity *target) {
    if (m_pTarget) {
        m_pTarget->release();
    }
    
    m_pTarget = target;
    m_pTarget->retain();
}


void GamePlayScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *event) {
    CCTouch *touch = (CCTouch *)pTouches->anyObject();
    CCPoint location = touch->getLocation();
    //CCLOG("--- touch location: %f, %f", location.x, location.y);
    
    MessageDispatcher::instance()->dispatchMessage(0, 0, m_pTarget->getID(), kMessageMoveToPosition, (void *)&location);
}
*/