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
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	mainSpr = CCSprite::create();

	CCSprite* bg = CCSprite::create("pause_dialog.png");
	bg->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	mainSpr->addChild(bg, -2);
	
	CCMenuItemImage* menuButton = CCMenuItemImage::create(
		"button.png",
		"buttonPress.png",
		this,
		menu_selector(PauseDialog::MenuCallback));

	menuButton->setScale(0.6f);
	menuButton->setPosition(ccp(origin.x + 250, origin.y + visibleSize.height - 965 + 110));

	CCMenuItemImage* resumeButton = CCMenuItemImage::create(
		"button.png",
		"buttonPress.png",
		this,
		menu_selector(PauseDialog::ResumeCallBack));
	resumeButton->setScale(0.6f);
	resumeButton->setPosition(ccp(origin.x + 536, origin.y + visibleSize.height - 965 + 110));

	CCMenu* menu = CCMenu::create(menuButton, resumeButton, NULL);
	menu->setPosition(origin);
	mainSpr->addChild(menu);

	CCLabelBMFont* lbMenu = CCLabelBMFont::create("MENU", "Mia_64.fnt");
	lbMenu->setScale(0.65f);
	lbMenu->setColor(ccc3(0,0,0));
	lbMenu->setPosition(ccp(origin.x + 250, origin.y + visibleSize.height - 965 + 110));
	mainSpr->addChild(lbMenu);

	CCLabelBMFont* lbResume = CCLabelBMFont::create("RESUME", "Mia_64.fnt");
	lbResume->setScale(0.65f);
	lbResume->setColor(ccc3(0,0,0));
	lbResume->setPosition(ccp(origin.x + 536, origin.y + visibleSize.height - 965 + 110));
	mainSpr->addChild(lbResume);

	//run
	this->addChild(mainSpr);

	mainSpr->setPosition(ccp(visibleSize.width/2 - mainSpr->getContentSize().width/2, 0));
	CCActionInterval* move = CCMoveTo::create(2, CCPointZero);
	CCAction* ease = CCEaseElasticOut::create(move);
	mainSpr->runAction(ease);

	return true;
}

void PauseDialog::MenuCallback( CCObject* pSender )
{
	CCScene *pScene = CCTransitionFade::create(0.5, MenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void PauseDialog::ResumeCallBack( CCObject* pSender )
{
	MainGameScene* parent = (MainGameScene*) this->getParent();
	parent->resumeCallback();
	this->removeFromParent();
}
