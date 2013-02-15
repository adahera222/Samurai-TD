//
//  AWLuaHelper.cpp
//  TD
//
//  Created by Yifeng Wu on 30/12/12.
//
//

#include "AWLuaHelper.h"
#include "lua/cocos2dx_support/CCLuaEngine.h"

USING_NS_CC;



void awExecuteLuaFile(const char *fileName) {
    cocos2d::CCLuaEngine *pEngine = cocos2d::CCLuaEngine::defaultEngine();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCString* pstrFileContent = CCString::createWithContentsOfFile(fileName);
    if (pstrFileContent)
    {
        pEngine->executeString(pstrFileContent->getCString());
    }
#else
    std::string path = cocos2d::CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(fileName);
    pEngine->addSearchPath(path.substr(0, path.find_last_of("/")).c_str());
    pEngine->executeScriptFile(path.c_str());
#endif
}


int awGetLuaInt(const char *key) {
    cocos2d::CCLuaEngine *pEngine = cocos2d::CCLuaEngine::defaultEngine();
    pEngine->cleanStack();
    
    lua_State *state = pEngine->getLuaState();
    
    lua_getglobal(state, key);
    int isnum = lua_isnumber(state, 1);
    
    if (isnum) {
        int result = (int)lua_tonumber(state, 1);
        //cocos2d::CCLog("--- result: %d", result);
        return result;
    }
    return 0;   // fail
}


double awGetLuaDouble(const char *key) {
    cocos2d::CCLuaEngine *pEngine = cocos2d::CCLuaEngine::defaultEngine();
    pEngine->cleanStack();

    lua_State *state = pEngine->getLuaState();
    
    lua_getglobal(state, key);
    int isnum = lua_isnumber(state, 1);
    
    if (isnum) {
        double result = (double)lua_tonumber(state, 1);
        //cocos2d::CCLog("--- result: %lf", result);
        return result;
    }
    return 0;   // fail
}


const char *awGetLuaString(const char *key) {
    cocos2d::CCLuaEngine *pEngine = cocos2d::CCLuaEngine::defaultEngine();
    pEngine->cleanStack();
    
    lua_State *state = pEngine->getLuaState();
    
    lua_getglobal(state, key);
    int isstring = lua_isstring(state, 1);
    
    if (isstring) {
        const char *retval = lua_tostring(state, 1);
        return retval;
    }
    return NULL;    // fail
}


const char *awGetLuaStringFromTable(lua_State *pl, const char *key) {
    // assumes table at 1
    
    lua_pushstring(pl, key);
    lua_gettable(pl, -2);
    
    if (!lua_isstring(pl, -1)) {
        CCLOG("---[C++]: Error: invalid type for key:'%s'",key);
        return NULL;
    }
    
    const char *retString = lua_tostring(pl, -1);
    //CCLOG("--- %s, %s", key, retString);
    lua_pop(pl, 1);
    
    return retString;
}


int awGetLuaIntFromTable(lua_State *pl, const char *key) {
    // assumes table at 1
    
    lua_pushstring(pl, key);
    lua_gettable(pl, -2);
    
    if (!lua_isnumber(pl, -1)) {
        if (lua_isstring(pl, -1)) {
            CCLog("---String !");
        };
        if (lua_isnil(pl, -1)) {
            CCLog("---Nil !");
        }
        CCLOG("---[C++]: Error: invalid type for key:'%s'",key);
        //int retInt = (int)lua_tonumber(pl, -1);
        //CCLOG("--- %s, %d", key, retInt);
        return NULL;
    }
    
    //const char *retString = lua_tostring(pl, -1);
    int retInt = (int)lua_tonumber(pl, -1);
    //CCLOG("--- %s, %d", key, retInt);
    lua_pop(pl, 1);
    
    return retInt;
}


double awGetLuaDoubleFromTable(lua_State *pl, const char *key) {
    // assumes table at 1
    
    lua_pushstring(pl, key);
    lua_gettable(pl, -2);
    
    if (!lua_isnumber(pl, -1)) {
        CCLOG("---[C++]: Error: invalid type for key:'%s'",key);
        return NULL;
    }
    
    //const char *retString = lua_tostring(pl, -1);
    double retDouble = (double)lua_tonumber(pl, -1);
    //CCLOG("--- %s, %lf", key, retDouble);
    lua_pop(pl, 1);
    
    return retDouble;
}


void awSetLuaTable(lua_State *pl, const char *tableKey) {
    lua_settop(pl, 0);  // Reset the statck
    
    lua_getglobal(pl, tableKey);    // get table
    
    if (!lua_istable(pl, 1)) {
        CCLog("---[C++]: Error: table for key:'%s' is not a valid table", tableKey);
        return ;
    }
}


lua_State *awGetLuaState() {
    return CCLuaEngine::defaultEngine()->getLuaState();
}