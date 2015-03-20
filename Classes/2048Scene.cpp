# include "2048Scene.h"
# include "MyScene.h"
# include <cstring>
# include <ctime>
# include <queue>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<b;i++)

const int xx[]= {0,0,-1,1};
const int yy[]= {-1,1,0,0};

CCSprite *g[16];
const int PP[]= {0,2,4,8,16,32,64,128,256,512,1024,2048};
//�±߶�Ӧ����

struct state
{
	int his[4][4];
	long long hispoint;
	void init(int tmp_[4][4],long long point_)
	{
		memcpy(his,tmp_,sizeof(his));
		hispoint=point_;
	}
};
deque<state>dq;
const int max_state=10;
//˫����б���� Undo ״̬
//������ʹ��STL

My2048Scene::My2048Scene()
{

}
My2048Scene::~My2048Scene()
{

}
CCScene* My2048Scene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();

    // 'layer' is an autorelease object
    My2048Scene *layer = My2048Scene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
bool My2048Scene::init()
{

    size.width=480,size.height=854;//��Ļ��С
    move_dis=75;//�ƶ������ж�


    CCSprite *background_2048=CCSprite::create("homepage.png");
    background_2048->setPosition(ccp(size.width/2,size.height*0.5));
    this->addChild(background_2048);
	//����ͼ

    CCSprite *coord_2048=CCSprite::create("2048-coord.png");
    coord_2048->setPosition(ccp(size.width/2,size.height*0.5));
    this->addChild(coord_2048);
	//����ͼ

    Mysize=coord_2048->getPosition();
    Mysize.width-=150,Mysize.height-=10;
    //CCLOG("%f %f\n",Mysize.width,Mysize.height);
	//���þ����еģ�0��0����λ��

    /*int i=0,j=1;
    CCSprite *sp1=CCSprite::create("5.png");
    sp1->setPosition(ccp(Mysize.width+100*j,Mysize.height-100*i));
    this->addChild(sp1);*/

    CCLabelTTF *My_restart_tmp =CCLabelTTF :: create("restart" ,"FZNHT.ttf",30);
    CCMenuItemLabel *My_restart =CCMenuItemLabel::create(My_restart_tmp,this,menu_selector(My2048Scene::menuCall_restart));
    My_restart->setPosition(ccp(size.width/4*3,size.height*0.6));

    CCLabelTTF *My_return_tmp =CCLabelTTF :: create("return" ,"FZNHT.ttf",30);
    CCMenuItemLabel *My_return =CCMenuItemLabel::create(My_return_tmp,this,menu_selector(My2048Scene::menuCall_return));
    My_return->setPosition(ccp(size.width/4,size.height*0.6));

	CCLabelTTF *My_undo_tmp=CCLabelTTF ::create("undo","FZNHT.ttf",30);
	CCMenuItemLabel *My_undo=CCMenuItemLabel::create(My_undo_tmp,this,menu_selector(My2048Scene::menuCall_undo));
	My_undo->setPosition(ccp(size.width/4*2,size.height*0.6));

    CCMenu *menu =CCMenu::create(My_restart,My_return,My_undo,NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
	//���restart,return,undo�˵�


    CCLabelTTF *Mypoint_borad=CCLabelTTF::create("Point  :","FZNHT.ttf",40);
    Mypoint_borad->setColor(ccc3(255,255,0));
    Mypoint_borad->setPosition(ccp(size.width/5,size.height*0.675));
    this->addChild(Mypoint_borad);

    Mypoint=CCLabelTTF::create("0","FZNHT.ttf",40);
    Mypoint->setColor(ccc3(0,255,255));
    //Mypoint->setAnchorPoint(ccp(size.width/5*4,size.height*0.675));
    Mypoint->setPosition(ccp(size.width/5*4,size.height*0.675));
    this->addChild(Mypoint);
	//������ʾ

    FOR(m,0,16)
    {
        int i=m/4,j=m%4;
        My2048[i][j]=0;
        CCString *str=CCString::createWithFormat("%d.png",My2048[i][j]);
        g[i*4+j]=CCSprite::create(str->getCString());
        g[i*4+j]->setPosition(ccp(Mysize.width+100*j,Mysize.height-100*i));
        this->addChild(g[i*4+j]);
		//��ʼ��ȫ������͸��ͼƬ
    }
    My2048Point=0;
    MyWin=false;
	Go_touch=true;
	//������Ч
	dq.clear();

    time_t t;
    time(&t);
    t%=1000;
    t*=t;
    srand(t);

    build();
    build();
	
	dq.pop_front();

    //setTouchEnabled(false);
    setTouchEnabled(true);
	//���ô���
    Myreverse=0;
    //My2048win();
    Overboard=NULL;
    return true;
}

void My2048Scene:: build()
{
    FOR(k,0,16)
    {
        int i=k/4,j=k%4;
        if(My2048[i][j]==0)
            Myque.push(k);
    }
	//���пո�����ӣ��������
    int m=CCRANDOM_0_1()*(Myque.size()-1)+1;
    //CCLOG("%d ",m);
    int tmp;
    while (m--&&!Myque.empty())
    {
        tmp=Myque.front();
        Myque.pop();
    }
    while(!Myque.empty())Myque.pop();
    m=tmp;
    int i=m/4,j=m%4;
    int or_2_4=CCRANDOM_0_1()*10;
    if(or_2_4>=8)
        My2048[i][j]=2;
    else
        My2048[i][j]=1;

	//�������2����4
	state tmp_state;
	tmp_state.init(My2048,My2048Point);
	while (dq.size()>max_state)
	{
		dq.pop_front();
	}
	dq.push_back(tmp_state);
	//״̬��˫����ж�β


    CCString *str=CCString::createWithFormat("%d.png",My2048[i][j]);
	g[i*4+j]->cleanup();
	g[i*4+j]->initWithFile(str->getCString());
    
    g[i*4+j]->setPosition(ccp(Mysize.width+100*j,Mysize.height-100*i));
	
	CCActionInterval *build_1=CCScaleTo::create(0.2f,1.5f);
	CCActionInterval *build_2=CCScaleTo::create(0.2f,1.0f);
	CCActionInterval *build_action=CCSequence::create(build_1,build_2,NULL);
	g[i*4+j]->runAction(build_action);
	//������ʱ�Ķ���Ч��
}

void My2048Scene::Myredis(float dt)
	{
	FOR(i,0,4)
		FOR(j,0,4)
		{
		CCString *str=CCString::createWithFormat("%d.png",My2048[i][j]);

		g[i*4+j]->cleanup();

		g[i*4+j]->initWithFile(str->getCString());

		g[i*4+j]->setPosition(ccp(Mysize.width+100*j,Mysize.height-100*i));

		//�ػ�
		}
	}


void My2048Scene::Mydisplay()
	{
	FOR(i,0,4)
		FOR(j,0,4)
		{
		if(b[i][j]==-1)continue;

		int x=b[i][j]/4,y=b[i][j]%4;

		CCActionInterval *move_to=CCMoveTo::create(0.2f,ccp(Mysize.width+100*y,Mysize.height-100*x));

		g[i*4+j]->runAction(move_to);
		}
	scheduleOnce(schedule_selector(My2048Scene::Myredis),0.2f);
	//�ƶ�������ɺ�0.2s���ػ�
	}

bool My2048Scene::My2048union(int m)
{
//�ϲ�
    bool flag=false;
	//�ж��Ƿ��ƶ����κ�һ��
    bool pointadd=false;
	//�Ƿ�ӷ���
	memset(b,-1,sizeof(b));
	//���� b ���ڼ�¼·��
    if(m==1)//left
    {
        FOR(i,0,4)
        {
            FOR(j,0,4)
            {
                if(My2048[i][j]==0)
					for(int k=j+1; k<4; k++)
						{
						if(My2048[i][k]==0)continue;
						int tmp=My2048[i][j];
						My2048[i][j]=My2048[i][k];
						My2048[i][k]=tmp;
						b[i][k]=i*4+j;
						flag=true;
						break;
						}
				
                for(int k=j+1; k<4; k++)
                {
                    if(My2048[i][k]==0)continue;
                    else if(My2048[i][k]==My2048[i][j])
                    {
                        My2048[i][j]++;
                        My2048[i][k]=0;
                        My2048Point+=PP[My2048[i][j]];
						b[i][k]=i*4+j;
                        flag=true;
                        pointadd=true;
                        break;
                    }
                    else
                        break;
                }
            }
        }

    }
    else if(m==2)//right
    {
        FOR(i,0,4)
        {
            for(int j=3; j>=0; j--)
            {
                if(My2048[i][j]==0)
					for(int k=j-1; k>=0; k--)
						{
						if(My2048[i][k]==0)continue;
						int tmp=My2048[i][j];
						My2048[i][j]=My2048[i][k];
						My2048[i][k]=tmp;
						b[i][k]=i*4+j;
						flag=true;
						break;
						}
				
                for(int k=j-1; k>=0; k--)
                {
                    if(My2048[i][k]==0)continue;
                    else if(My2048[i][k]==My2048[i][j])
                    {
                        My2048[i][j]++;
                        My2048[i][k]=0;
                        My2048Point+=PP[My2048[i][j]];
						b[i][k]=i*4+j;
                        flag=true;
                        pointadd=true;
                        break;
                    }
                    else
                        break;
                }
            }
            
        }
    }
    else if(m==3)//down
    {
        FOR(i,0,4)
        {
            for(int j=3; j>=0; j--)
            {
                if(My2048[j][i]==0)
					for(int k=j-1; k>=0; k--)
						{
						if(My2048[k][i]==0)continue;
						int tmp=My2048[j][i];
						My2048[j][i]=My2048[k][i];
						My2048[k][i]=tmp;
						b[k][i]=j*4+i;
						flag=true;
						break;
						}
				
                for(int k=j-1; k>=0; k--)
                {
                    if(My2048[k][i]==0)continue;
                    else if(My2048[k][i]==My2048[j][i])
                    {
                        My2048[j][i]++;
                        My2048[k][i]=0;
                        My2048Point+=PP[My2048[j][i]];
						b[k][i]=j*4+i;
                        pointadd=true;
                        flag=true;
                        break;
                    }
                    else
                        break;
                }
            }
        }
    }
    else if(m==4)//up
    {
        FOR(i,0,4)
        {
            FOR(j,0,4)
            {
                if(My2048[j][i]==0)
					for(int k=j+1; k<4; k++)
						{
						if(My2048[k][i]==0)continue;
						int tmp=My2048[j][i];
						My2048[j][i]=My2048[k][i];
						My2048[k][i]=tmp;
						b[k][i]=j*4+i;
						flag=true;
						break;
						}
				
                for(int k=j+1; k<4; k++)
                {
                    if(My2048[k][i]==0)continue;
                    else if(My2048[k][i]==My2048[j][i])
                    {
                        My2048[j][i]++;
                        My2048[k][i]=0;
                        My2048Point+=PP[My2048[j][i]];
						b[k][i]=j*4+i;
                        pointadd=true;
                        flag=true;
                        break;
                    }
                    else
                        break;
                }
            }
        }
    }
	if(flag)
	{
		Go_touch=false;
		Mydisplay();
		//�����Ҫ�ƶ�������ͣ��Ӧ��������������ټ���
	}
    if(pointadd)
    {
        Mypointadd();
    }

    return flag;
}

void My2048Scene::Mypointadd()
{
//�ӷ�
    Mypoint->setString(CCString::createWithFormat("%lld",My2048Point)->getCString());
}
void My2048Scene::Myrebui(float dt)
	{
		build();
	}
void My2048Scene::Mytouchflag(float dt)
	{
		Go_touch=true;
		//�ָ�����
	}

void My2048Scene::gameover(float dt)
	{
	bool gameflag=false;
	gameflag=My2048Cheack();
	if(MyWin)
		{
		//system("pause");
		//CCLOG("Win\n");
		My2048win();
		}
	else if(!gameflag)
		{
		//system("pause");
		//CCLOG("over\n");
		My2048over();
		}
	}
void My2048Scene::My2048Move()
{
// ��ʼ������
    bool flag=false;
    if(Myreverse==0)
        return ;
    else
        flag=My2048union(Myreverse);
	//�ж��з���ͽ��кϲ����������Ƿ�ɹ��ƶ���
    if(!flag)
        return;
	
	
	//�ȴ��ƶ�������ɺ���ִ��
	scheduleOnce(schedule_selector(My2048Scene::Myrebui),0.2f);
	scheduleOnce(schedule_selector(My2048Scene::Mytouchflag),0.3f);	
	scheduleOnce(schedule_selector(My2048Scene::gameover),0.2f);
    
}
void My2048Scene::My2048win()
{
//��Ϸʤ������

    Overboard=CCSprite::create("overboard.png");
    Overboard->setPosition(ccp(Mysize.width+150,Mysize.height-150));
    this->addChild(Overboard,100);

    CCLabelTTF *Win_flag=CCLabelTTF::create("YOU WIN","FZNHT.ttf",40);
    Win_flag->setColor(ccc3(255,0,0));
    CCSize tmp=Overboard->getPosition();
    Win_flag->setPosition(ccp(tmp.width-125,tmp.height-125));
    Overboard->addChild(Win_flag);

    CCLabelTTF *board_point=CCLabelTTF::create("0","FZNHT.ttf",30);
    board_point->setString(CCString::createWithFormat("%lld",My2048Point)->getCString());
    board_point->setColor(ccc3(0,0,0));
    board_point->setPosition(ccp(tmp.width/2,tmp.height/6));
    Overboard->addChild(board_point);
    this->setTouchEnabled(false);
}
void My2048Scene::My2048over()
{
//��Ϸ��������

    Overboard=CCSprite::create("overboard.png");
    Overboard->setPosition(ccp(Mysize.width+150,Mysize.height-150));
    this->addChild(Overboard,100);

    CCLabelTTF *Lost_flag=CCLabelTTF::create("YOU LOST","FZNHT.ttf",40);
    Lost_flag->setColor(ccc3(0,255,255));
    CCSize tmp=Overboard->getPosition();
    Lost_flag->setPosition(ccp(tmp.width-125,tmp.height-125));
    Overboard->addChild(Lost_flag);

    CCLabelTTF *board_point=CCLabelTTF::create("0","FZNHT.ttf",30);
    board_point->setString(CCString::createWithFormat("%lld",My2048Point)->getCString());
    board_point->setColor(ccc3(0,0,0));
    board_point->setPosition(ccp(tmp.width/2,tmp.height/6));
    Overboard->addChild(board_point);
    this->setTouchEnabled(false);
}

bool My2048Scene::My2048Cheack()
{
//���ʤ������ʧ��
    bool flag=false;
    FOR(i,0,4)
    FOR(j,0,4)
    {
        if(My2048[i][j]==11)MyWin=true;
    }
	//2^11=2048
    FOR(i,0,4)
    FOR(j,0,4)
    {
        FOR(k,0,4)
        {
            int x=i+xx[k];
            int y=j+yy[k];
            if(x<0||y<0||x>=4||y>=4)continue;

            if(My2048[i][j]==0||My2048[i][j]==My2048[x][y])
                return true;
        }
    }
    return false;
}

void My2048Scene::get_ture_callback()
{
//�жϴ�������
    Myreverse=0;
    CCPoint ans=ccpSub(startP,thendP);
    if(ans.x*ans.x+ans.y*ans.y<move_dis*move_dis)return;
    //����̫�̲���Ϊһ���ƶ�
	if (fabs(ans.x)>fabs(ans.y))
	//���ƾ����������
    {
        if (ans.x>move_dis)
        {
            //CCLOG("l");
            Myreverse=1;
        }
        else if(ans.x<-move_dis)
        {
            //CCLOG("r");
            Myreverse=2;
        }
        else
            return;
    }
    else
    {
        if (ans.y>move_dis)
        {
            //CCLOG("d");
            Myreverse=3;
        }
        else if(ans.y<-move_dis)
        {
            //CCLOG("u");
            Myreverse=4;
        }
        else
            return;
    }
	if(Myreverse==0)return;
	MoveFlag=1;
    My2048Move();

}

void My2048Scene::onEnter()
{
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,false);
	
}

void My2048Scene::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
bool My2048Scene::ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent)
{
//��ʼ����
	if(Go_touch==false)return false;
	//�������Ч������ִ�У��رմ�����Ӧ
    MoveFlag=0;
    startP=pTouch->getLocation();

    return true;
}

void My2048Scene::ccTouchMoved(CCTouch *pTouch,CCEvent *pEvent)
{
//�������ƶ���
	if(MoveFlag)return;
	thendP=pTouch->getLocation();
	Myreverse=0;
	get_ture_callback();

}

void My2048Scene::ccTouchEnded(CCTouch *pTouch,CCEvent *pEvent)
{
//��������
	if(MoveFlag)return;
    thendP=pTouch->getLocation();
    Myreverse=0;
    get_ture_callback();
}

void My2048Scene::menuCall_restart(CCObject *pSender)
{
//restart ����Ч��
    if(Overboard!=NULL)
        Overboard->removeFromParentAndCleanup(true);
	FOR(i,0,16)
		g[i]->removeFromParentAndCleanup(true);
    CCScene *temps=My2048Scene::scene();
    CCDirector::sharedDirector()->replaceScene(temps);
}
void My2048Scene::menuCall_return(CCObject *pSender)
{
//return ����Ч��
    CCScene *temps=MyScene::scene();
    CCDirector::sharedDirector()->replaceScene(temps);
}

void My2048Scene::menuCall_undo(CCObject *pSender)
{
//undo ����Ч��
	if (dq.size()<=1)return;
	dq.pop_back();
	//CCLOG("UNDO");
	state tmp_state;
	tmp_state=dq.back();

	memcpy(My2048,tmp_state.his,sizeof(tmp_state.his));
	scheduleOnce(schedule_selector(My2048Scene::Myredis),0.0f);
	My2048Point=tmp_state.hispoint;
	Mypointadd();
}