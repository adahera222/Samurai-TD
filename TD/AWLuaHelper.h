//
//  AWLuaHelper.h
//  TD
//
//  Created by Yifeng Wu on 30/12/12.
//
//

#ifndef TD_AWLuaHelper_h
#define TD_AWLuaHelper_h

#include "cocos2d.h"
#include "CCLuaEngine.h"

void awExecuteLuaFile(const char *fileName);

int awGetLuaInt(const char *key);

double awGetLuaDouble(const char *key);

const char *awGetLuaString(const char *key);

const char *awGetLuaStringFromTable(lua_State *pl, const char *key);
int awGetLuaIntFromTable(lua_State *pl, const char *key);
double awGetLuaDoubleFromTable(lua_State *pl, const char *key);

void awSetLuaTable(lua_State *pl, const char *tableKey);

lua_State *awGetLuaState();


#endif
