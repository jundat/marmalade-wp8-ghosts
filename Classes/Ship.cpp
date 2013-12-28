#include "Ship.h"
#include "ObjectLayer.h"
#include "Global.h"
#include "MyMacro.h"

USING_NS_CC;


Ship::~Ship()
{

}

bool Ship::init()
{
	if (!GameObject::init())
	{
		return false;
	}

	this->setHp(G_PLAYER_HP);

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	m_sprite = CCSprite::create("ship.png");
	m_sprite->setPosition(CCPointZero);
	this->addChild(m_sprite);

	m_EffectLayer = EffectLayer::create();
	this->addChild(m_EffectLayer, 100);

	//////////////////////////////////////////////////////////////////////////
	
	this->scheduleUpdate();
	return true;
}

void Ship::update( float delta )
{
	//limit on screen
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	
	float x = getPositionX();
	float y = getPositionY();
	float w_2 = boundingBox().size.width/2;
	float h_2 = boundingBox().size.height/2;

	LIMIT_VALUE(x, origin.x + w_2, origin.x + visibleSize.width - w_2);
	LIMIT_VALUE(y, origin.y + h_2, origin.y + visibleSize.height - h_2);
	this->setPosition(x, y);
}

void Ship::HitBullet( int damage )
{
	m_hp -= damage;
	m_hp  = (m_hp > 0) ? m_hp : 0;

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
		m_EffectLayer->AddExploisionEff(3, p1);
		m_EffectLayer->AddExploisionEff(3, p2);
		m_EffectLayer->AddExploisionEff(3, p3);
	}
}

void Ship::Dead()
{
	this->setVisible(false);
}

void Ship::Restart()
{
	this->setHp(G_PLAYER_HP);
	this->setVisible(true);
}
