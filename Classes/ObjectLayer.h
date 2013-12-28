#ifndef __GAME_OBJECT_MANAGER_H__
#define __GAME_OBJECT_MANAGER_H__

#include "cocos2d.h"
#include "Global.h"
#include "MyMacro.h"
#include "Ship.h"
#include "EffectLayer.h"

USING_NS_CC;

class ObjectLayer : public cocos2d::CCLayer
{
public:
	ObjectLayer(){}
	~ObjectLayer(){
		RELEASE(m_arrEnemies);

		if (_rt != NULL)
		{
			_rt->release();
		}
	};

    virtual bool init();
	CREATE_FUNC(ObjectLayer);
	virtual void update(float delta);

public:
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void ScheduleGenerateEnemy(float dt);
	void ContinueGame();
	void RestartGame();
	void Pause();
	void Resume();

public:
	void AfterDeadEffectCallback();

private:
	void ScheduleCheckCollision(float dt);

private:
	CC_SYNTHESIZE(int, m_score, Score);
	CC_SYNTHESIZE(bool, m_isEndGame, IsEndGame);
	CC_SYNTHESIZE(Ship*, m_player, Player);
	CCLabelBMFont* m_labelScore;
	CCLabelBMFont* m_labelHp;
		
	CCPoint m_lastPoint;
	
	CCArray* m_arrEnemies;
	float m_timeToGenerateEnemy;
	EffectLayer* m_EffectLayer;
	//pixel check collision
	static CCRenderTexture* _rt;
};

#endif // __GAME_OBJECT_MANAGER_H__
