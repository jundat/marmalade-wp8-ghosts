#include "LoseDialog.h"
#include "MainGameScene.h"
#include "MenuScene.h"

USING_NS_CC;

bool LoseDialog::init()
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
	
	CCLabelBMFont* lb1 = CCLabelBMFont::create("Game over!", "Mia_64.fnt");
	//lbResume->setScale(0.65f);
	lb1->setColor(ccc3(0,0,0));
	lb1->setPosition(ccp(768/2, 1280/2 + 80));
	mainSpr->addChild(lb1);

	CCLabelBMFont* lb2 = CCLabelBMFont::create("Again?", "Mia_64.fnt");
	//lbResume->setScale(0.65f);
	lb2->setColor(ccc3(0,0,0));
	lb2->setPosition(ccp(768/2, 1280/2));
	mainSpr->addChild(lb2);

	CCMenuItemImage* menuButton = CCMenuItemImage::create(
		"button.png",
		"buttonPress.png",
		this,
		menu_selector(LoseDialog::menuCallBack));

	menuButton->setScale(0.6f);
	menuButton->setPosition(ccp(250, 1280 - 965 + 110));

	CCMenuItemImage* resumeButton = CCMenuItemImage::create(
		"button.png",
		"buttonPress.png",
		this,
		menu_selector(LoseDialog::playAgainCallBack));
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

	CCLabelBMFont* lbResume = CCLabelBMFont::create("RETRY", "Mia_64.fnt");
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

void LoseDialog::playAgainCallBack( CCObject* pSender )
{
	MainGameScene* parent = (MainGameScene*) this->getParent();
	parent->playAgainCallback();
	this->removeFromParent();
}

void LoseDialog::menuCallBack( CCObject* pSender )
{
	CCScene *pScene = CCTransitionFade::create(0.5, MenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}
