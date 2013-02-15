//
//  TestScene.cpp
//  TD
//
//  Created by Yifeng Wu on 01/01/13.
//
//

#include "TestScene.h"
#include "AWLuaHelper.h"

USING_NS_CC;


CCScene *TestScene::scene() {
    CCScene *scene = CCScene::create();
    TestScene *layer = TestScene::create();
    scene->addChild(layer);
    return scene;
}


bool TestScene::init() {
    if (CCLayer::init()) {
        TestAWLuaGetIntDoubleFromTable();
        return true;
    }
    return false;
}


void TestScene::TestAWLuaGetIntDoubleFromTable() {
    CCLuaEngine *pEngine = CCLuaEngine::defaultEngine();
    lua_State *state = pEngine->getLuaState();
    
    awExecuteLuaFile("towerInfo.lua");
    
    awSetLuaTable(state, "test");
    
    int a = awGetLuaIntFromTable(state, "myInt");
    CCLog("--- result: %d", a);
    
    int b = awGetLuaIntFromTable(state, "herInt");
    CCLog("--- b: %d", b);
    
    double c = awGetLuaDoubleFromTable(state, "myDouble");
    CCLog("--- c: %lf", c);
}
