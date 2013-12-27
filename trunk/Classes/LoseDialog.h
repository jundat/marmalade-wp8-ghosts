#ifndef __LOSE_DIALOG_H__
#define __LOSE_DIALOG_H__

#include "cocos2d.h"
USING_NS_CC;

class LoseDialog : public cocos2d::CCLayer
{
public:
	LoseDialog():CCLayer(){};
	~LoseDialog(){};
    virtual bool init();
	CREATE_FUNC(LoseDialog);

	CC_SYNTHESIZE(CCSprite*, mainSpr, MainSprite);

public:
	void MenuCallBack(CCObject* pSender);
	void PlayAgainCallBack(CCObject* pSender);
};

#endif // __LOSE_DIALOG_H__
