#include "ObjectLayer.h"
#include "Enemy.h"
#include "Global.h"


USING_NS_CC;

Enemy::Enemy(float difficulty, int MOVE_TYPE) : GameObject()
{
	this->setDifficulty(difficulty);
}

bool Enemy::init()
{
	if (!GameObject::init())
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//////////////////////////////////////////////////////////////////////////

	int n = (int)(CCRANDOM_0_1() * 3) + 1;
	CCString* s = CCString::createWithFormat("enemy_%d.png", n);
	m_sprite = CCSprite::create(s->getCString());

	m_sprite->setPosition(CCPointZero);
	this->addChild(m_sprite);

	m_EffectLayer = EffectLayer::create();
	this->addChild(m_EffectLayer, 100);

	//////////////////////////////////////////////////////////////////////////
	this->setDamage(1);
	this->setHp(1);

	static float MOVE_TIME = 2.0f; //default
	MOVE_TIME -= 0.005f;
	m_moveTime = MOVE_TIME;

	//random source and dest
	CCSize size = this->boundingBox().size;
	float sx, sy, dx, dy;
	int rdChoosePosition;

	sy = (CCRANDOM_0_1() * (visibleSize.height + 2 * size.height)) - size.height;
	dy = (CCRANDOM_0_1() * (visibleSize.height + 2 * size.height)) - size.height;
	
	rdChoosePosition = (int)(CCRANDOM_0_1() * 2); //0, 1

	if (rdChoosePosition == 0) //left
	{
		sx = - size.width;
		dx = visibleSize.width + size.width;
	}
	else
	{
		sx = visibleSize.width + size.width;
		dx = - size.width;
	}

	this->setPosition(ccp(sx, sy));

	this->runAction(
		CCSequence::create(
		CCMoveTo::create(m_moveTime, ccp(dx, dy)),
		CCCallFunc::create(this, callfunc_selector(Enemy::SetDead)),
		NULL));
	//////////////////////////////////////////////////////////////////////////
	

	//////////////////////////////////////////////////////////////////////////
	return true;
}

void Enemy::HitBullet(int damage)
{
	m_hp -= damage;

	if (m_hp > 0)
	{
		//small effect explosion
		m_EffectLayer->AddExploisionEff(2, CCPointZero);
	}
	else
	{
		CCSize s = getContentSize();
		CCPoint p1 = CCPointZero;
		CCPoint p2 = ccp(-s.width/2, s.height/2);
		CCPoint p3 = ccp(s.width/2, s.height/2);

		//big effect explosion
		float t1 = m_EffectLayer->AddExploisionEff(3, p1);
		float t2 = m_EffectLayer->AddExploisionEff(3, p2);
		float t3 = m_EffectLayer->AddExploisionEff(3, p3);
		t1 = (t1 > t2) ? t1 : t2;
		t1 = (t1 > t3) ? t1 : t3;

		CCSequence* sequence = CCSequence::create(
			CCDelayTime::create(t1),
			CCCallFunc::create(this, callfunc_selector(Enemy::removeFromParent)),
			NULL
			);
		this->runAction(sequence);
	}
}

//////////////////////////////////////////////////////////////////////////

void Enemy::SetDead()
{
	m_hp = 0;
}

//////////////////////////////////////////////////////////////////////////