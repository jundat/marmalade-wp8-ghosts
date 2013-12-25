#include "EffectLayer.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool EffectLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    return true;
}

float EffectLayer::AddExploisionEff(int enemySize, CCPoint p )
{
	enemySize = 3;

	int NUM_FRAME = 12;
	float TIME_ANIMATION = 0.1f;

	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("explosion_3.plist");

	CCString* strSpriteName = CCString::createWithFormat("explosion_%d (1).png", enemySize);
	CCSprite* m_pSprite1 = CCSprite::createWithSpriteFrameName(strSpriteName->getCString());

	m_pSprite1->setPosition(p);
	this->addChild(m_pSprite1);

	CCArray* animFrames = CCArray::createWithCapacity(NUM_FRAME);
	for(int i = 1; i < NUM_FRAME; i++) 
	{
		strSpriteName = CCString::createWithFormat("explosion_%d (%d).png", enemySize, i);
		CCSpriteFrame* frame = cache->spriteFrameByName( strSpriteName->getCString() );
		animFrames->addObject(frame);
	}

	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, TIME_ANIMATION);
	m_pSprite1->runAction(
		CCSequence::create(
			CCAnimate::create(animation), 
			CCCallFuncN::create(this, callfuncN_selector(EffectLayer::RemoveEffCallback)),
			NULL
	));

	return NUM_FRAME * TIME_ANIMATION;
}

void EffectLayer::RemoveEffCallback(CCNode* pSender)
{
	this->removeChild(pSender);
}

void EffectLayer::PreLoad()
{
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("explosion_3.plist");
}
