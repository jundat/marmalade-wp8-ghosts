#include "RankDialog.h"
#include "MenuScene.h"
#include "ParseClient.h"

USING_NS_CC;

bool RankDialog::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

	m_isActive = true;

	mainSpr = CCSprite::create();

	//////////////////////////////////////////////////////////////////////////

	CCSprite* bg = CCSprite::create("dialog.png");
	bg->setPosition(ccp(768/2, 1280/2));
	mainSpr->addChild(bg, -2);
	
	m_lbTitle = CCLabelBMFont::create("Connecting", "Mia_64.fnt");
	m_lbTitle->setColor(ccc3(0,0,0));
	m_lbTitle->setPosition(ccp(768/2, 1280/2 + 80));
	mainSpr->addChild(m_lbTitle);

	m_lbRank = CCLabelBMFont::create("...", "Mia_64.fnt");
	m_lbRank->setColor(ccc3(0,0,0));
	m_lbRank->setPosition(ccp(768/2, 1280/2));
	mainSpr->addChild(m_lbRank);
	
	//

	CCMenuItemImage* menuButton = CCMenuItemImage::create(
		"button.png",
		"buttonPress.png",
		this,
		menu_selector(RankDialog::menuCallBack));

	menuButton->setScale(0.6f);
	menuButton->setPosition(ccp(768/2, 1280 - 965 + 110));

	CCMenu* menu = CCMenu::create(menuButton, NULL);
	menu->setPosition(CCPointZero);
	mainSpr->addChild(menu);

	CCLabelBMFont* lbMenu = CCLabelBMFont::create("OK", "Mia_64.fnt");
	lbMenu->setScale(0.65f);
	lbMenu->setColor(ccc3(0,0,0));
	lbMenu->setPosition(ccp(768/2, 1280 - 965 + 110));
	mainSpr->addChild(lbMenu);

	//run

	this->addChild(mainSpr);

	mainSpr->setPosition(ccp(768/2 - mainSpr->getContentSize().width/2, 0));
	CCActionInterval* move = CCMoveTo::create(2, CCPointZero);
	CCAction* ease = CCEaseElasticOut::create(move);
	mainSpr->runAction(ease);

	ParseClient::sharedParseClient()->callCloudFunction(
		"submitScore", 
		"{\"score\": 123}",
		httpresponse_selector(RankDialog::onHttpRequestCompleted), 
		"submitScore");

    return true;
}

void RankDialog::menuCallBack( CCObject* pSender )
{
	CCSequence* seq = CCSequence::create(
		CCMoveTo::create(0.25f, ccp(- 768, 0)),
		CCCallFunc::create(this, callfunc_selector( RankDialog::afterSlideCallback)),
		NULL);
	mainSpr->runAction(seq);
}

void RankDialog::afterSlideCallback()
{
	MenuScene* par = (MenuScene*)this->getParent();
	par->active();
	m_isActive = false;
	this->removeFromParent();
}

void RankDialog::onHttpRequestCompleted( CCHttpClient *sender, CCHttpResponse *response )
{
	if (!m_isActive) return;

	if (!response)
	{
		return;
	}

	//Show info
	CCLOG("-----------------BEGIN-------------------");
	CCLOG("Request: [%s] completed", response->getHttpRequest()->getTag());
	CCLOG("Status: [%i]", response->getResponseCode());

	if (!response->isSucceed())
	{
		CCLog("Request Failed: Error buffer: %s", response->getErrorBuffer());
 		m_lbTitle->setCString("Disconnected :(");
	}
	else
	{
		std::vector<char> *buffer = response->getResponseData();
		std::string str(buffer->begin(), buffer->end());
		CCLOG("Content: %s", str.c_str());

		m_lbTitle->setCString("Your Rank");
		m_lbRank->setCString(str.c_str());
	}	

	CCLOG("-----------------END-------------------");
}
