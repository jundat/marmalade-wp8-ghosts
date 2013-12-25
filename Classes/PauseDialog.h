#ifndef __PAUSE_DIALOG_H__
#define __PAUSE_DIALOG_H__

#include "cocos2d.h"
#include "CCParallaxNodeExtras.h"
USING_NS_CC;

class PauseDialog : public cocos2d::CCLayer
{
public:
	PauseDialog():CCLayer(){};
	~PauseDialog(){};
    virtual bool init();
	CREATE_FUNC(PauseDialog);

	CC_SYNTHESIZE(CCSprite*, mainSpr, MainSprite);

public:
	void MenuCallback(CCObject* pSender);
	void ResumeCallBack(CCObject* pSender);
};

#endif // __PAUSE_DIALOG_H__
