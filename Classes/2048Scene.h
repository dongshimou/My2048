#pragma once
#include "cocos2d.h"
#include <queue>
using namespace std;
using namespace cocos2d;

class My2048Scene:public CCLayer
	{
	public:
		My2048Scene();
		~My2048Scene();
		
		static CCScene * scene();
		
		void menuCall_restart(CCObject *pSender);
		void menuCall_return(CCObject *pSender);
		void menuCall_undo(CCObject *pSender);

		virtual void build();
		virtual bool init(); 
		virtual void My2048Move();
		virtual bool My2048Cheack();
		virtual bool My2048union(int m);

		void Myredis(float dt);
		void Myrebui(float dt);
		void Mytouchflag(float dt);
		void gameover(float dt);

		void Mydisplay();
		void Mypointadd();
		void My2048over();
		void My2048win();
		long long My2048Point;
		int My2048[4][4];
		CCLabelTTF *Mypoint;
		CCSize Mysize;
		CCSize size;
		CCSprite *Overboard;
		void onEnter();
		void onExit();
		virtual bool ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent);
		virtual void ccTouchMoved(CCTouch *pTouch,CCEvent *pEvent);
		virtual void ccTouchEnded(CCTouch *pTouch,CCEvent *pEvent);

		CREATE_FUNC(My2048Scene);
	private:
		bool MoveFlag;
		CCPoint startP,thendP;
		float move_dis;
		void get_ture_callback();
		int Myreverse;
		bool MyWin;
		queue<int>Myque;
		int b[4][4];
		bool Go_touch;
	};
