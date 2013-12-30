#ifndef __RANK_DIALOG_H__
#define __RANK_DIALOG_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "HttpClient.h"
#include "ParseClient.h"

USING_NS_CC;
USING_NS_CC_EXT;

class RankDialog : public cocos2d::CCLayer
{
public:
	~RankDialog(){};
    virtual bool init();
	CREATE_FUNC(RankDialog);

	CC_SYNTHESIZE(CCSprite*, mainSpr, MainSprite);
	CC_SYNTHESIZE(CCLabelBMFont*, m_lbTitle, LbTitle);
	CC_SYNTHESIZE(CCLabelBMFont*, m_lbRank, LtRank);
	
	bool m_isActive;

	void menuCallBack(CCObject* pSender);
	void afterSlideCallback();
	void onHttpRequestCompleted(CCHttpClient *sender, CCHttpResponse *response);
};

#endif // __RANK_DIALOG_H__
