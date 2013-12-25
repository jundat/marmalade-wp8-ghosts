#include "MainGameScene.h"
#include "AudioManager.h"
#include "MenuScene.h"
#include "LoseDialog.h"
#include "PauseDialog.h"
#include "ObjectLayer.h"


USING_NS_CC;

CCScene* MainGameScene::scene()
{
    CCScene *scene = CCScene::create();
    MainGameScene *layer = MainGameScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainGameScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
	
	m_isPause = false;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    m_BackgroundLayer = BackgroundLayer::create();
	this->addChild(m_BackgroundLayer);

	m_ObjLayer = ObjectLayer::create();
	this->addChild(m_ObjLayer);

	CCMenuItemImage *menuItem = CCMenuItemImage::create(
		"btnHome.png",
		"btnHomePress.png",
		this,
		menu_selector(MainGameScene::menuCallback));
	menuItem->setPosition(ccp(origin.x + visibleSize.width - menuItem->getContentSize().width/2,
		origin.y + visibleSize.height - menuItem->getContentSize().height/2));
	CCMenu* pMenu = CCMenu::create(menuItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	m_sprTutorial = CCSprite::create("tutorial.png");
	m_sprTutorial->setPosition(ccp(visibleSize.width/2, visibleSize.height/2 - 300));
	this->addChild(m_sprTutorial);
	m_sprTutorial->runAction(CCSequence::create(
		CCDelayTime::create(1.0f),
		CCFadeOut::create(1.0f),
		NULL
		));

	this->setKeypadEnabled(true);

    return true;
}

void MainGameScene::menuCallback(CCObject* pSender)
{
	if (m_ObjLayer->getIsEndGame() == false && m_isPause == false)
	{
		m_isPause = true;
		m_ObjLayer->Pause();
		m_BackgroundLayer->Pause();
		PauseDialog* lose = PauseDialog::create();
		this->addChild(lose);
	}
}

void MainGameScene::resumeCallback()
{
	m_isPause = false;
	m_ObjLayer->Resume();
	m_BackgroundLayer->Resume();
}

void MainGameScene::keyBackClicked()
{
	menuCallback(NULL);
}

void MainGameScene::showEndGame( int score )
{
	m_BackgroundLayer->Pause();
	LoseDialog* lose = LoseDialog::create();
	this->addChild(lose);
}

void MainGameScene::playAgainCallback()
{
	m_BackgroundLayer->Resume();
	m_ObjLayer->RestartGame();
}

