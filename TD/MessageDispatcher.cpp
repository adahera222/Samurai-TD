//
//  MessageDispatcher.cpp
//  TD
//
//  Created by Yifeng Wu on 26/12/12.
//
//

#include "MessageDispatcher.h"
#include "BaseGameEntity.h"
#include "GameModel.h"
#include "AWTime.h"


USING_NS_CC;

static MessageDispatcher *sg_pSharedMessageDispatcher;

//
// Construction && Deconstruction - BEGIN
//
MessageDispatcher::~MessageDispatcher() {
    CC_SAFE_DELETE(m_pPriorityQ);
}


void MessageDispatcher::purge() {
    CC_SAFE_DELETE(sg_pSharedMessageDispatcher);
}


MessageDispatcher *MessageDispatcher::instance() {
    if (!sg_pSharedMessageDispatcher) {
        sg_pSharedMessageDispatcher = new MessageDispatcher();
        sg_pSharedMessageDispatcher->init();
    }
    
    return sg_pSharedMessageDispatcher;
}


bool MessageDispatcher::init() {
    m_pPriorityQ = new cocos2d::CCSet();

    return true;
}
// END


//
// Functions - BEGIN
//

void MessageDispatcher::discharge(BaseGameEntity *entity, const Telegram *telegram) {
    if (!entity->handleMessage(telegram)) {
        /*
        CCLog("--- Message could not be handled");
        CCLog("---      sender: %d", telegram->sender);
        CCLog("---      receiver: %d", telegram->receiver);
        CCLog("---      message: %d", telegram->message);
        CCLog("---      delay: %lf", telegram->dispatchTime);
         */
    }
}


void MessageDispatcher::dischargeSystemMessage(const Telegram *telegram) {
    if (!GameModel::instance()->handleMessage(telegram)) {
        
    }
}


void MessageDispatcher::dispatchMessage(double delay, int sender, int receiver, int message, void *extraInfo) {
    Telegram telegram(sender, receiver, message, delay, extraInfo);
    
    BaseGameEntity *pReceiver = GameModel::instance()->getEntityForID(receiver);
    if (delay <= 0.0) { // instant message
        discharge(pReceiver, &telegram);
    }
    else {  // delayed message
        double curTime = currentTimeInSEC();
        telegram.dispatchTime = curTime + delay;
        m_pPriorityQ->addObject(&telegram); // retained by the queue
    }

}


void MessageDispatcher::dispatchMessage(double delay, int sender, BaseGameEntity *pReceiver, int message, void *extraInfo) {
    Telegram telegram(sender, pReceiver->getID(), message, delay, extraInfo);

    if (delay <= 0) {   // instant message
        discharge(pReceiver, &telegram);
    }
    else {  // delayed message
        
    }
}


void MessageDispatcher::dispatchSystemMessage(double delay, int sender, int message, void *extraInfo) {
    Telegram telegram(sender, -1, message, delay, extraInfo);
    
    if (delay <= 0.0) { // instant message
        dischargeSystemMessage(&telegram);
    }
    else {  // delayed message

    }
}


void MessageDispatcher::dispatchDelayedMessages() {
    // ...
}
// END