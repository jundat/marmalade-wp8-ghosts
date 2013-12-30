#include "MenuScene.h"
#include "MainGameScene.h"
#include "AudioManager.h"
#include "AboutScene.h"
#include "DataManager.h"
#include "RankDialog.h"

USING_NS_CC;

CCScene* MenuScene::scene()
{
    CCScene *scene = CCScene::create();
    MenuScene *layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    /////////////////////////////
	m_isDeactive = false;

	CCSprite* bg = CCSprite::create("bg_menu.png");
	bg->setPosition(ccp(768/2, 1280/2));
	this->addChild(bg, 0);

	CCSprite* menuTop = CCSprite::create("menu_top.png");
	menuTop->setPosition(ccp(768/2, 1280/2));
	this->addChild(menuTop, 0);

	CCString* s = CCString::createWithFormat("YOUR BEST: %d", DataManager::GetInstance()->GetCurrenHighScore());
	CCLabelBMFont* lbScore = CCLabelBMFont::create(s->getCString(), "Mia_64.fnt");
	lbScore->setPosition(ccp(768/2, 1280/2 - 170));
	this->addChild(lbScore, 0);
	lbScore->runAction(CCFadeIn::create(1.0f));

	//

    CCMenuItemImage *playItem = CCMenuItemImage::create(
                                        "new_button.png",
                                        "new_button_press.png",
                                        this,
                                        menu_selector(MenuScene::playCallback));
    
	playItem->setPosition(ccp(- playItem->getContentSize().width/2, 1280/2 - 290));

	playItem->runAction(CCEaseElasticOut::create(CCMoveTo::create(1.9f, ccp(768/2, 1280/2 - 290))));

	//

	CCMenuItemImage *rankItem = CCMenuItemImage::create(
		"rank_button.png",
		"rank_button_press.png",
		this,
		menu_selector(MenuScene::rankCallback));

	rankItem->setPosition(ccp(768 + rankItem->getContentSize().width/2, 
		playItem->getPositionY() - playItem->getContentSize().height/2 - rankItem->getContentSize().height/2));
	rankItem->runAction(CCEaseElasticOut::create(CCMoveTo::create(1.9f, ccp(768/2, 
		playItem->getPositionY() - playItem->getContentSize().height/2 - rankItem->getContentSize().height/2))));
	
	//

	CCMenuItemImage *aboutItem = CCMenuItemImage::create(
		"about_button.png",
		"about_button_press.png",
		this,
		menu_selector(MenuScene::aboutCallback));

	aboutItem->setPosition(ccp(- aboutItem->getContentSize().width/2, 
		rankItem->getPositionY() - rankItem->getContentSize().height/2 - aboutItem->getContentSize().height/2));
	aboutItem->runAction(CCEaseElasticOut::create(CCMoveTo::create(1.9f, ccp(768/2, 
		rankItem->getPositionY() - rankItem->getContentSize().height/2 - aboutItem->getContentSize().height/2))));

	//

	CCMenuItemImage *exitItem = CCMenuItemImage::create(
		"exit_button.png",
		"exit_button_press.png",
		this,
		menu_selector(MenuScene::exitCallback));

	exitItem->setPosition(ccp(768 + exitItem->getContentSize().width/2,
		aboutItem->getPositionY() - aboutItem->getContentSize().height/2 - exitItem->getContentSize().height/2 - 10));
	exitItem->runAction(CCEaseElasticOut::create(CCMoveTo::create(1.9f, ccp(768/2, 
		aboutItem->getPositionY() - aboutItem->getContentSize().height/2 - exitItem->getContentSize().height/2))));

	//////////////////////////////////////////////////////////////////////////
	
	CCMenuItem* soundOn = CCMenuItemImage::create("sound_on.png", NULL, NULL);
	CCMenuItem* soundOff = CCMenuItemImage::create("sound_off.png", NULL, NULL);
	CCMenuItemToggle* soundToggle = CCMenuItemToggle::createWithTarget(this,  menu_selector(MenuScene::soundCallback), soundOn, soundOff, NULL);

	if(AudioManager::sharedAudioManager()->IsEnableBackground())
	{
		soundToggle->setSelectedIndex(0);
	}
	else
	{
		soundToggle->setSelectedIndex(1);
	}
	
	soundToggle->setPosition(ccp(- soundToggle->getContentSize().width/2, soundToggle->getContentSize().height/2 + 20));

	soundToggle->runAction(CCEaseElasticOut::create(CCMoveTo::create(1.9f, ccp(soundToggle->getContentSize().width/2 + 2, soundToggle->getContentSize().height/2 + 20))));

	//////////////////////////////////////////////////////////////////////////
	
    CCMenu* pMenu = CCMenu::create(playItem, rankItem, aboutItem, exitItem, soundToggle, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

	AudioManager::sharedAudioManager()->PlayBackground("background.mp3");

	EffectLayer::PreLoad();

	this->setKeypadEnabled(true);

    return true;
}

void MenuScene::soundCallback( CCObject* pSender )
{
	if (m_isDeactive) return;

	if(AudioManager::sharedAudioManager()->IsEnableBackground())
	{
		AudioManager::sharedAudioManager()->SetEnableBackground(false);
		AudioManager::sharedAudioManager()->SetEnableEffect(false);

		//
		AudioManager::sharedAudioManager()->StopBackground();
	}
	else
	{
		AudioManager::sharedAudioManager()->SetEnableBackground(true);
		AudioManager::sharedAudioManager()->SetEnableEffect(true);

		//
		AudioManager::sharedAudioManager()->PlayBackground("background.mp3");
	}
}

void MenuScene::playCallback(CCObject* pSender)
{
	if (m_isDeactive) return;

    CCScene *pScene = CCTransitionFade::create(0.5, MainGameScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void MenuScene::rankCallback( CCObject* pSender )
{
	deactive();

	RankDialog* dialog = RankDialog::create();
	this->addChild(dialog, 10);
}

void MenuScene::aboutCallback( CCObject* pSender )
{
	if (m_isDeactive) return;

	CCScene *pScene = CCTransitionFade::create(0.5, AboutScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void MenuScene::exitCallback( CCObject* pSender )
{
	if (m_isDeactive) return;

	CCDirector::sharedDirector()->end();
}

void MenuScene::keyBackClicked()
{
	if (m_isDeactive) return;

	exitCallback(NULL);
}

void MenuScene::active()
{
	m_isDeactive = false;
}

void MenuScene::deactive()
{
	m_isDeactive = true;
}
