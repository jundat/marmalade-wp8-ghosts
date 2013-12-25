#include "MenuScene.h"
#include "AboutScene.h"

USING_NS_CC;

CCScene* AboutScene::scene()
{
    CCScene *scene = CCScene::create();
    AboutScene *layer = AboutScene::create();
    scene->addChild(layer);
    return scene;
}

bool AboutScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCSprite* bg = CCSprite::create("bg_menu.png");
	bg->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(bg, 0);

	CCSprite* setting_top = CCSprite::create("about.png");
	setting_top->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(setting_top, 0);

	CCMenuItemImage *backItem = CCMenuItemImage::create(
		"back_button.png",
		"back_button_press.png",
		this,
		menu_selector(AboutScene::menuCallback));

	backItem->setPosition(ccp(origin.x + visibleSize.width/2,
		origin.y + backItem->getContentSize().height - 3));
	
	CCMenu* pMenu = CCMenu::create(backItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
	
	this->setKeypadEnabled(true);

    return true;
}

void AboutScene::menuCallback(CCObject* pSender)
{
	CCScene *pScene = CCTransitionFade::create(0.5, MenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void AboutScene::keyBackClicked()
{
	menuCallback(NULL);
}
