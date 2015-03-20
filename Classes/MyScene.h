#pragma once
#include "cocos2d.h"

using namespace cocos2d;
class MyScene :public CCLayer
	{
	public:
		MyScene(void);
		~MyScene(void);
		virtual bool init();
		static CCScene * scene();

		void menuCall_start(CCObject *pSender);
		void menuCall_thend(CCObject *pSender);

		CCSize size ;

		CREATE_FUNC(MyScene);
	};

