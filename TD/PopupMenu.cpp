//
//  PopupMenu.cpp
//  TD
//
//  Created by Yifeng Wu on 13/01/13.
//
//

#include "PopupMenu.h"
#include "GameModel.h"

USING_NS_CC;

#define kMenuR      50

//
// Construction && Deconstruction - BEGIN
//
PopupMenu::~PopupMenu() {
    m_pMenu->removeFromParentAndCleanup(true);
    CC_SAFE_RELEASE(m_pMenu);
}


bool PopupMenu::init() {
    do {
        m_pMenu = CCMenu::create();
        GameModel::instance()->getBatch()->getParent()->addChild(m_pMenu);
        m_pMenu->setVisible(false);     // Invisible by default.
        m_pMenu->retain();
        
        //CCMenuItemLabel *cancel = CCMenuItemLabel::create("Fal", cocos2d::CCObject *target, SEL_MenuHandler selector)
        
        m_pFreeMenuItems = CCArray::create();
        m_pFreeMenuItems->retain();
        
        return true;
    } while (0);
    
    return false;
}
// - END

//
// Functions - BEGIN
//
void PopupMenu::displayMenuAt(cocos2d::CCPoint &position) {
    m_pMenu->setVisible(true);
    m_pMenu->setPosition(position);
}


void PopupMenu::closeMenu() {
    m_pMenu->setVisible(false);
    for (int i=0; i<m_pMenu->getChildrenCount(); i++) {
        CCObject *obj = m_pMenu->getChildren()->objectAtIndex(i);
        m_pFreeMenuItems->addObject(obj);
        //CCLog("free items: %d", m_pFreeMenuItems->count());
    }
    
    m_pMenu->removeAllChildrenWithCleanup(true);
}


void PopupMenu::setChoice(const char *info, CCObject *target, SEL_MenuHandler selector, MenuItemLocation loc, int extraInfo) {
    CCMenuItemLabel *freeItem;
    CCLabelTTF *label = CCLabelTTF::create(info, "Arial", 20);
    
    if ((freeItem = (CCMenuItemLabel *)getFreeMenuItem())) {
        freeItem->setLabel(label);
        m_pMenu->addChild(freeItem);
        m_pFreeMenuItems->removeObject(freeItem);
    }
    else {
        freeItem = CCMenuItemLabel::create(label);
        m_pMenu->addChild(freeItem);    // Store extra info in tag
    }
    
    freeItem->setTarget(target, selector);
    freeItem->setTag(extraInfo);
    placeMenuItem(freeItem, loc);
}


CCMenuItem *PopupMenu::getFreeMenuItem() {
    if (m_pFreeMenuItems->count() > 0) {
        CCMenuItem *retval = (CCMenuItem *)m_pFreeMenuItems->objectAtIndex(0);
        return retval;
    }
    return NULL;
}


void PopupMenu::placeMenuItem(cocos2d::CCMenuItem *item, MenuItemLocation loc) {
    CCPoint pos;
    
    switch (loc) {
        case kTopMid:
            pos = ccp(0, kMenuR);
            break;
            
        case kTopLeft:
            pos = ccp(-kMenuR/1.4, kMenuR/1.4);
            break;
            
        case kTopRight:
            pos = ccp(kMenuR/1.4, kMenuR/1.4);
            break;
            
        case kLowerMid:
            pos = ccp(0, -kMenuR);
            break;
            
        case kLowerRight:
            pos = ccp(kMenuR/1.4, -kMenuR/1.4);
            break;
            
        default:
            break;
    }
    
    item->setPosition(pos);
}