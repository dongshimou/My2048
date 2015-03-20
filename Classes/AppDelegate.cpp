#include "AppDelegate.h"
#include "MyScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
    //���캯��
}

AppDelegate::~AppDelegate()
{
    //��������
}
bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    // ��ʼ��������
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    // ����OpenGL��ͼ
    pDirector->setOpenGLView(pEGLView);

    // turn on display FPS
    // ��FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    // ����֡
    pDirector->setAnimationInterval(1.0 / 60);

    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(480,854,kResolutionShowAll);
    //����Ӧ����


    // create a scene. it's an autorelease object
    // ����һ������
    CCScene *pScene = MyScene::scene();

    // run
    // ��ʼ
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
// �����̨����ʱ������ִ������Ĳ���
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    // ����ʲô��ȫ����ͣ
}

// this function will be called when the app is active again
// ��̨��������ʱ�򣬳����������
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    // ������Դ����ִ��
}
