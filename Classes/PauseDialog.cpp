#include "PauseDialog.h"
#include "MainGameScene.h"
#include "MenuScene.h"

USING_NS_CC;

bool PauseDialog::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	mainSpr = CCSprite::create();

	//////////////////////////////////////////////////////////////////////////

	CCSprite* bg = CCSprite::create("dialog.png");
	bg->setPosition(ccp(768/2, 1280/2));
	mainSpr->addChild(bg, -2);

	CCLabelBMFont* lb1 = CCLabelBMFont::create("Pause!", "Mia_64.fnt");
	//lbResume->setScale(0.65f);
	lb1->setColor(ccc3(0,0,0));
	lb1->setPosition(ccp(768/2, 1280/2));
	mainSpr->addChild(lb1);
	
	CCMenuItemImage* menuButton = CCMenuItemImage::create(
		"button.png",
		"buttonPress.png",
		this,
		menu_selector(PauseDialog::menuCallback));

	menuButton->setScale(0.6f);
	menuButton->setPosition(ccp(250, 1280 - 965 + 110));

	CCMenuItemImage* resumeButton = CCMenuItemImage::create(
		"button.png",
		"buttonPress.png",
		this,
		menu_selector(PauseDialog::resumeCallBack));
	resumeButton->setScale(0.6f);
	resumeButton->setPosition(ccp(536, 1280 - 965 + 110));

	CCMenu* menu = CCMenu::create(menuButton, resumeButton, NULL);
	menu->setPosition(CCPointZero);
	mainSpr->addChild(menu);

	CCLabelBMFont* lbMenu = CCLabelBMFont::create("MENU", "Mia_64.fnt");
	lbMenu->setScale(0.65f);
	lbMenu->setColor(ccc3(0,0,0));
	lbMenu->setPosition(ccp(250, 1280 - 965 + 110));
	mainSpr->addChild(lbMenu);

	CCLabelBMFont* lbResume = CCLabelBMFont::create("RESUME", "Mia_64.fnt");
	lbResume->setScale(0.65f);
	lbResume->setColor(ccc3(0,0,0));
	lbResume->setPosition(ccp(536, 1280 - 965 + 110));
	mainSpr->addChild(lbResume);

	//run
	this->addChild(mainSpr);

	mainSpr->setPosition(ccp(768/2 - mainSpr->getContentSize().width/2, 0));
	CCActionInterval* move = CCMoveTo::create(2, CCPointZero);
	CCAction* ease = CCEaseElasticOut::create(move);
	mainSpr->runAction(ease);

	return true;
}

void PauseDialog::menuCallback( CCObject* pSender )
{
	CCScene *pScene = CCTransitionFade::create(0.5, MenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void PauseDialog::resumeCallBack( CCObject* pSender )
{
	MainGameScene* parent = (MainGameScene*) this->getParent();
	parent->resumeCallback();
	this->removeFromParent();
}
