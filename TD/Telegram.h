//
//  Telegram.h
//  TD
//
//  Created by Yifeng Wu on 25/12/12.
//
//

#ifndef TD_Telegram_h
#define TD_Telegram_h

#include "cocos2d.h"
#include "MessageTypes.h"

struct Telegram : public cocos2d::CCObject {
    unsigned int    sender;
    unsigned int    receiver;
    int             message;
    double          dispatchTime;
    void *          extraInfo;      // weak reference
    
    Telegram (int sender, int receiver, int message, double dispatchTime, void *extraInfo) : sender(sender), receiver(receiver), message(message), dispatchTime(dispatchTime), extraInfo(extraInfo) {}
    
    /*
    static Telegram *create(int sender, int receiver, int message, double dispatchTime, void *extraInfo) {
        Telegram *telegram = new Telegram(sender, receiver, message, dispatchTime, extraInfo);
        if (telegram) {
            telegram->autorelease();
            return telegram;
        }
        CC_SAFE_DELETE(telegram);
        return NULL;
    }
     */
};

#endif
