#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "ObjectLayer.h"
#include "EffectLayer.h"


USING_NS_CC;

class MainGameScene : public cocos2d::CCLayer
{
public:
	~MainGameScene() {
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
	}
    virtual bool init();
    static cocos2d::CCScene* scene();
	CREATE_FUNC(MainGameScene);
	virtual void keyBackClicked();
	
	CC_SYNTHESIZE(bool, m_isPause, IsPause);

	CCSprite* m_sprTutorial;

public:
	void showEndGame(int score);
	void playAgainCallback();
	void menuCallback(CCObject* pSender);
	void resumeCallback();

private:
	BackgroundLayer* m_BackgroundLayer;
	ObjectLayer* m_ObjLayer;
};

#endif // __MAIN_GAME_SCENE_H__
