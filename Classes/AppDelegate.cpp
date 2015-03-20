#include "AppDelegate.h"
#include "MyScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
    //构造函数
}

AppDelegate::~AppDelegate()
{
    //析构函数
}
bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    // 初始化导演类
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    // 设置OpenGL视图
    pDirector->setOpenGLView(pEGLView);

    // turn on display FPS
    // 打开FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    // 设置帧
    pDirector->setAnimationInterval(1.0 / 60);

    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(480,854,kResolutionShowAll);
    //自适应缩放


    // create a scene. it's an autorelease object
    // 创建一个场景
    CCScene *pScene = MyScene::scene();

    // run
    // 开始
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
// 程序后台运行时，程序执行下面的操作
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    // 声音什么的全部暂停
}

// this function will be called when the app is active again
// 后台切入程序的时候，程序继续运行
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    // 程序资源继续执行
}
