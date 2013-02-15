//
//  TDAppDelegate.cpp
//  TD
//
//  Created by Yifeng Wu on 19/12/12.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "GamePlayScene.h"
#include "script_support/CCScriptSupport.h"
#include "CCLuaEngine.h"

#include "TestScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
    //CCScriptEngineManager::purgeSharedManager();

}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    pDirector->enableRetinaDisplay(true);
    
    CCTexture2D::PVRImagesHavePremultipliedAlpha(true);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 30);
    
    // register lua engine  --- by GW
    CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);

    // create a scene. it's an autorelease object
    //CCScene *pScene = HelloWorld::scene();
    CCScene *pScene = GamePlayScene::scene();
    //CCScene *pScene = TestScene::scene();
    
    // run
    pDirector->runWithScene(pScene);
    
    /*
     #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
     CCString* pstrFileContent = CCString::createWithContentsOfFile("hello.lua");
     if (pstrFileContent)
     {
     pEngine->executeString(pstrFileContent->getCString());
     }
     #else
     std::string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("hello.lua");
     pEngine->addSearchPath(path.substr(0, path.find_last_of("/")).c_str());
     pEngine->executeScriptFile(path.c_str());
     #endif
     */

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
