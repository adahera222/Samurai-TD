//
//  TestScene.h
//  TD
//
//  Created by Yifeng Wu on 01/01/13.
//
//

#ifndef __TD__TestScene__
#define __TD__TestScene__

#include <iostream>
#include "cocos2d.h"

class TestScene : public cocos2d::CCLayer {
    void TestAWLuaGetIntDoubleFromTable();

    
public:
    static cocos2d::CCScene *scene();
    
    CREATE_FUNC(TestScene);
    
    bool init();
};

#endif /* defined(__TD__TestScene__) */
