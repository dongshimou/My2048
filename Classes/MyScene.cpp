#include "MyScene.h"
#include "2048Scene.h"

MyScene::MyScene(void)
{
}


MyScene::~MyScene(void)
{
}
CCScene* MyScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    MyScene *layer = MyScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
bool MyScene::init()
{
    //CCSize size =CCDirector::sharedDirector()->getWinSize();
    // ��ȡ��Ļ��С

    //size=CCDirector::sharedDirector()->getWinSize();

    size.width=480,size.height=854;

    CCSprite *homepage=CCSprite::create("homepage.png");
    homepage->setPosition(ccp(size.width/2,size.height*0.5));
    this->addChild(homepage);

    //CCSprite *bg=CCSprite ::create("HelloWorld.png");
    //bg->setPosition(ccp(size.width/2,size.height/2));			//ccp=CCPoint
    //this->addChild(bg);

    /*CCSprite *sp0=CCSprite::create("icon.png");
    sp0->setPosition(ccp(100,100));
    this->addChild(sp0);*/
    /*
    CCSprite *sp1=CCSprite::create("CloseNormal.png");
    sp1->setPosition(ccp(100,100));
    bg->addChild(sp1);*/

    /*
    CCSprite *sp1=CCSprite::create("icon.png");
    sp1->setPosition(ccp(size.width*0.2,size.height*0.7));
    this->addChild(sp1);

    CCSprite *sp2=CCSprite::create("icon.png",CCRect(28,28,29,29));//����,������
    sp2->setPosition(ccp(size.width*0.4,size.height*0.7));
    this->addChild(sp2);

    CCTexture2D *Texture=CCTextureCache::sharedTextureCache()->addImage("icon.png");
    // ����2D����

    CCSprite *sp3=CCSprite::createWithTexture(Texture);
    sp3->setPosition(ccp(size.width*0.6,size.height*0.7));
    this->addChild(sp3);

    CCSprite *sp4=CCSprite::createWithTexture(Texture,CCRect(0,0,40,40));
    sp4->setPosition(ccp(size.width*0.8,size.height*0.7));
    this->addChild(sp4);

    CCSpriteFrame *frame=CCSpriteFrame::create("icon.png",CCRect(0,0,57,57));
    // ����֡
    CCSprite *sp5=CCSprite::createWithSpriteFrame(frame);
    sp5->setPosition(ccp(size.width*0.3,size.height*0.3));
    this->addChild(sp5);
    //sp5->setScale(2);						//�Ŵ�����
    //sp5->setScale(0.5);					//��Сһ��
    //sp5->setRotation(30);					//˳ʱ����ת30��
    //sp5->setRotation(-30);				//��ʱ����ת30��
    //sp5->setSkewX(30);					//ˮƽ˳ʱ����б30��
    //sp5->setSkewX(-30);					//ˮƽ��ʱ����б30��
    //sp5->setVisible(false);				//�Ƿ�ɼ�
    //sp5->setColor(ccc3(255,0,0));			//������ɫ
    //sp5->setOpacity(30);					//͸���� ͸��0-255��͸��
    //sp5->setTexture(CCTextureCache::sharedTextureCache()->addImage("CloseNormal.png"));
    										//������ʾ��ͼƬ

    // ����һ�ֻ���֡�ķ�ʽ��ʹ��img.plist

    */


    /*CCLabelTTF *laber1 =CCLabelTTF :: create("fuck" ,"consola",25);
    laber1->setPosition(ccp(size.width/2,size.height*0.7));
    laber1->setColor(ccc3(255,255,0));
    this->addChild(laber1);*/
    //����


    /*CCLabelTTF *laber1 =CCLabelTTF :: create("start" ,"consola",50);
    CCMenuItemLabel *item1 =CCMenuItemLabel::create(laber1,this,menu_selector(MyScene::menuCall_start));
    item1->setPosition(ccp(size.width/2,size.height*0.7));
    */


    CCMenuItemImage *item_start=CCMenuItemImage :: create("start-normal.png","start-select.png",this,menu_selector(MyScene::menuCall_start));
    item_start->setPosition(ccp(size.width/2,size.height*0.5));
	//��ʼ�˵�

    CCMenuItemImage *item_thend=CCMenuItemImage :: create("thend-normal.png","thend-select.png",this,menu_selector(MyScene::menuCall_thend));
    item_thend->setPosition(ccp(size.width/2,size.height*0.3));
	//�����˵�

    CCMenu *menu =CCMenu::create(item_start,item_thend,NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
	//�������˵�

    CCLabelTTF *My=CCLabelTTF::create("dongshimou@gmail.com","FZNHT.ttf",40);
    My->setPosition(ccp(size.width/2,size.height/10));
    this->addChild(My);


    return true;
}
void MyScene::menuCall_start(CCObject *pSender)
{
    //system("pause");
    CCScene *temps=My2048Scene::scene();
    CCDirector::sharedDirector()->replaceScene(temps);
	//��ʼ������Ϸ������
}
void MyScene::menuCall_thend(CCObject *pSender)
{
    //system("pause");
	//�������
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
