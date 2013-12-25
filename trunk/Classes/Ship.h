#ifndef __SHIP_H__
#define __SHIP_H__

#include "cocos2d.h"
#include "GameObject.h"
#include "EffectLayer.h"

USING_NS_CC;

class Ship : public GameObject
{
public:
	Ship():GameObject(){}
	~Ship();
	virtual bool init();
	CREATE_FUNC(Ship); //static function: new, init, autorelease, return reference

private:
	CC_SYNTHESIZE(int, m_hp, Hp);
	EffectLayer* m_EffectLayer;

public:
	virtual void update(float delta);
	void HitBullet(int damage);
	void Dead();
	void Restart();
};

#endif //__SHIP_H__