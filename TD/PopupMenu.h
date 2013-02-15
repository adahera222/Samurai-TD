//
//  PopupMenu.h
//  TD
//
//  Created by Yifeng Wu on 13/01/13.
//
//

#ifndef __TD__PopupMenu__
#define __TD__PopupMenu__

#include <iostream>
#include "cocos2d.h"

enum MenuItemLocation {
    kTopMid = 1,
    kTopLeft = 2,
    kTopRight = 3,
    kLowerMid = 4,
    kLowerRight = 5,
    };


class PopupMenu : public cocos2d::CCObject {
    cocos2d::CCMenu *m_pMenu;   // strong reference
    cocos2d::CCArray *m_pFreeMenuItems;     // strong reference
    
    cocos2d::CCMenuItem *getFreeMenuItem();
    
    cocos2d::CCMenuItem *m_pCancelButton;
    
    void placeMenuItem(cocos2d::CCMenuItem *item, MenuItemLocation loc);
    
public:
    ~PopupMenu();
    CREATE_FUNC(PopupMenu);
    bool init();

    void displayMenuAt(cocos2d::CCPoint &position);
    void closeMenu();
    void setChoice(const char *info, cocos2d::CCObject *target,  cocos2d::SEL_MenuHandler selector, MenuItemLocation loc, int extraInfo);
};

#endif /* defined(__TD__PopupMenu__) */
