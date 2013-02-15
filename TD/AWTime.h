//
//  AWTime.h
//  TD
//
//  Created by Yifeng Wu on 26/12/12.
//
//

#ifndef __TD__AWTime__
#define __TD__AWTime__

#include <iostream>
#include <time.h>
#include "cocos2d.h"

//
// Time
//

long currentTimeInMS() {
    
    struct cocos2d::cc_timeval now;
    
    cocos2d::CCTime::gettimeofdayCocos2d(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec /1000.0)/10;
}


double currentTimeInSEC() {
    return currentTimeInMS()/1000.0;
}

#endif /* defined(__TD__AWTime__) */
