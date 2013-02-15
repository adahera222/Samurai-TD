//
//  MessageDispatcher.h
//  TD
//
//  Created by Yifeng Wu on 26/12/12.
//
//

#ifndef __TD__MessageDispatcher__
#define __TD__MessageDispatcher__

#include <iostream>
#include "cocos2d.h"
#include "Telegram.h"

class BaseGameEntity;


/**
 @brief This class is responsible for message dispatching.
 
 It can dispatch 2 types of message:
    1. instant message
    2. delayed message (not finished yet)
 
 It is a singleton.
 */
class MessageDispatcher : public cocos2d::CCObject {
    cocos2d::CCSet *m_pPriorityQ;   // need to be changed

    // send the telegram to specified entity
    void discharge(BaseGameEntity *entity, const Telegram *telegram);
    void dischargeSystemMessage(const Telegram *telegram);
    
public:
    //
    // Construction && Deconstruction
    //
    ~MessageDispatcher();
    
    // need to be called when MessageDispatcher is no longer needed
    static void purge();
    
    static MessageDispatcher *instance();
    
    bool init();
    
    //
    // Functions
    //
    void dispatchMessage(double delay, int sender, int receiver, int message, void *extraInfo);
    void dispatchMessage(double delay, int sender, BaseGameEntity *receiver, int message, void *extraInfo);
    
    void dispatchSystemMessage(double delay, int sender, int message, void *extraInfo);
    
    void dispatchDelayedMessages();
};

#endif /* defined(__TD__MessageDispatcher__) */
