//
//  MapTouchLayer.cpp
//  TD
//
//  Created by Yifeng Wu on 29/12/12.
//
//

#include "MapTouchLayer.h"
#include "GameModel.h"

USING_NS_CC;

MapTouchLayer::~MapTouchLayer() {
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


MapTouchLayer *MapTouchLayer::create(CCNode *gameMap) {
    MapTouchLayer *layer = new MapTouchLayer();
    if (layer && layer->initWithGameMap(gameMap)) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return NULL;
}


bool MapTouchLayer::initWithGameMap(CCNode *gameMap) {
    if (CCLayer::init()) {
        m_pGameMap = gameMap;
        
        registerWithTouchDispatcher();
        
        return true;
    }
    return false;
}


//
// Human Interaction - BEGIN
//
void MapTouchLayer::registerWithTouchDispatcher() {
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
}


bool MapTouchLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    m_uPrevPos = pTouch->getLocation(); // gl coord
    return true;
}


void MapTouchLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    
    m_uCurPos = pTouch->getLocation();  // gl coord
    CCPoint offset = ccpSub(m_uCurPos, m_uPrevPos);
    CCPoint newPos = ccpAdd(m_pGameMap->getPosition(), offset);
    newPos = GameModel::instance()->boundGamingLayer(newPos);
    
    m_pGameMap->setPosition(newPos);
    
    // update the map location in game model
    GameModel::instance()->getMapManager()->setMapLocation(m_pGameMap->getPosition());
    
    m_uPrevPos = m_uCurPos;
}
