//
//  BaseEntity.cpp
//  TD
//
//  Created by Yifeng Wu on 26/01/13.
//
//

#include "BaseEntity.h"
#include "ComponentBase.h"
#include "AWLuaHelper.h"

USING_NS_CC;


// Construction && Deconstruction
//------------------------------------

BaseEntity::~BaseEntity() {
    CCArray *integers = m_pComponents->allKeys();
    for (int i=0; i<integers->count(); i++) {
        CCInteger *integer = (CCInteger *)integers->objectAtIndex(i);
        int iKey = integer->getValue();
        ((ComponentBase *)m_pComponents->objectForKey(iKey))->clean();
    }
    CC_SAFE_RELEASE_NULL(m_pComponents);
    
    CC_SAFE_RELEASE_NULL(m_pActionList);
}


BaseEntity *BaseEntity::createWithFile(const char *file) {
    BaseEntity *retval = new BaseEntity();
    if (retval && retval->initWithFile(file)) {
        retval->autorelease();
        return retval;
    }
    CC_SAFE_DELETE(retval);
    return NULL;
}


bool BaseEntity::initWithFile(const char *file) {
    
    // execute file && get lua state
    //-------------------------------
    awExecuteLuaFile(file);
    
    CCLuaEngine *pEngine = CCLuaEngine::defaultEngine();
    pEngine->cleanStack();
    
    lua_State *state = pEngine->getLuaState();
    
    // parse components
    //-------------------------------
    awSetLuaTable(state, "components");
    
    int numComponents = awGetLuaIntFromTable(state, "num_components");
    CCArray *components = CCArray::create();
    for (int i=0; i<numComponents; i++) {
        CCString *sComponentN = CCString::createWithFormat("component_%d", i);
        
        components->addObject(sComponentN);
    }
    
    for (int i=0; i<numComponents; i++) {
        CCString *sComponentN = (CCString *)components->objectAtIndex(i);
    
        // use factory to create component
    }
    
    return true;
}



// Getters && Setters
//------------------------------------

unsigned int BaseEntity::getID() const {
    return m_uID;
}


void BaseEntity::update(float dt) {
    m_pActionList->update(dt);
}


