#include "Item.h"
#include "Global.h"
USING_NS_CC;


Item::Item(int type, float vy, CCPoint position) : GameObject()
{
	this->setItemType(type);
	this->setVy(vy);
	this->setPosition(position);
}

Item::~Item()
{

}

bool Item::init()
{
	if (!GameObject::init())
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//////////////////////////////////////////////////////////////////////////
	this->setVx(0);

	if (m_type == G_ITEM_UPGRADE_BULLET)
	{
		m_sprite = CCSprite::create("item_upgrade_bullet.png");
	} 
	else if (m_type == G_ITEM_ARMOR)
	{
		m_sprite = CCSprite::create("item_armor.png");
	}
	else if (m_type == G_ITEM_BOOM)
	{
		m_sprite = CCSprite::create("item_boom.png");
	}

	this->addChild(m_sprite);

	//////////////////////////////////////////////////////////////////////////

	this->scheduleUpdate();
	return true;
}

void Item::update( float delta )
{
	this->setPositionX(m_vx * delta * 1000 + this->getPositionX());
	this->setPositionY(m_vy * delta * 1000 + this->getPositionY());
}
