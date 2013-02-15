//
//  StateMachine.h
//  IM-Big-Devil
//
//  Created by Yifeng Wu on 15/12/12.
//
//

#ifndef __IM_Big_Devil__StateMachine__
#define __IM_Big_Devil__StateMachine__

#include <iostream>
#include "cocos2d.h"
#include "State.h"
#include "ComponentBase.h"

template <class entity_type>
class StateMachine : public ComponentBase {
private:
    // all are weak references
    entity_type *m_pAgent;
    
    CC_SYNTHESIZE(State<entity_type> *, m_pCurrentState, CurrentState);
    CC_SYNTHESIZE(State<entity_type> *, m_pPreviousState, PreviousState);
    CC_SYNTHESIZE(State<entity_type> *, m_pGlobalState, GlobalState);   // global state handles more global situations, if entities wants to kill itself, it should call here.
    
    
public:
    //
    // Construction && Deconstruction
    //
    static StateMachine<entity_type> *create(entity_type *agent) {
        StateMachine<entity_type> *sm = new StateMachine<entity_type>();
        if (sm && sm->init(agent)) {
            sm->autorelease();
            return sm;
        }
        CC_SAFE_DELETE(sm);
        return NULL;
    }
    
    
    static StateMachine<entity_type> *create(entity_type *agent, State<entity_type> *globalState, State<entity_type> *defaultState) {
        StateMachine<entity_type> *retval = new StateMachine<entity_type>();
        if (retval && retval->init(agent, globalState, defaultState)) {
            retval->autorelease();
            return retval;
        }
        CC_SAFE_DELETE(retval);
        return NULL;
    }


    bool init(entity_type *agent) {
        m_pAgent = agent;
        m_eType = kStateMachineComponent;
        
        return true;
    }
    
    
    bool init(entity_type *agent, State<entity_type> *globalState, State<entity_type> *defaultState) {
        if (init(agent)) {
            m_pGlobalState = globalState;
            changeState(defaultState);
            
            return true;
        }
        return false;
    }
    
    //
    // Logics
    //
    void changeState(State<entity_type> *pNewState) {
        if (!pNewState) {
            //cocos2d::CCLog("--- new state is NULL");
            return ;
        }
    
        m_pPreviousState = m_pCurrentState;
        if (m_pCurrentState) {
            m_pCurrentState->exit(m_pAgent);
        }
        m_pCurrentState = pNewState;
        m_pCurrentState->enter(m_pAgent);
    }
    
    
    void revertToPreviousState() {
        changeState(m_pPreviousState);
    }
    

    void update(float dt) const {
        if (m_pCurrentState)
            m_pCurrentState->execute(m_pAgent, dt);
        
        if (m_pGlobalState)
            m_pGlobalState->execute(m_pAgent, dt);
    }
    
    
    bool handleMessage(const Telegram *telegram) {
        if (m_pCurrentState && m_pCurrentState->onMessage(m_pAgent, telegram)) {
            return true;
        }

        if (m_pGlobalState && m_pGlobalState->onMessage(m_pAgent, telegram)) {
            return true;
        }
        
        // all attempts to handle the message fail
        return false;
    }
};

#endif /* defined(__IM_Big_Devil__StateMachine__) */
