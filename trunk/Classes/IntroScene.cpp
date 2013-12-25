#include "MenuScene.h"
#include "IntroScene.h"

USING_NS_CC;

CCScene* IntroScene::scene()
{
    CCScene *scene = CCScene::create();
    IntroScene *layer = IntroScene::create();
    scene->addChild(layer);
    return scene;
}

bool IntroScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCSprite* bg = CCSprite::create("intro.png");
	bg->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(bg, 0);
	
	bg->runAction(CCSequence::create(
		CCFadeIn::create(2.0f),
		CCDelayTime::create(1.0f),
		CCFadeOut::create(0.5f),
		CCCallFunc::create(this, callfunc_selector(IntroScene::MenuCallback)),
		NULL));

    return true;
}

void IntroScene::MenuCallback()
{
	CCScene *pScene = CCTransitionFade::create(0.5, MenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(pScene);
}
