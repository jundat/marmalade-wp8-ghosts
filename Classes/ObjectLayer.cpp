#include "ObjectLayer.h"
#include "Global.h"
#include "AudioManager.h"
#include "Enemy.h"
#include "EffectLayer.h"
#include "MainGameScene.h"
#include "CollisionDetection.h"
#include "LevelLoader.h"
#include "DataManager.h"

USING_NS_CC;

//pixel check collision
CCRenderTexture* ObjectLayer::_rt = NULL;

// on "init" you need to initialize your instance
bool ObjectLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	//////////////////////////////////////////////////////////////////////////
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	this->setTouchEnabled(true);
	//////////////////////////////////////////////////////////////////////////

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//////////////////////////////////////////////////////////////////////////

	m_arrEnemies = new CCArray();
	m_arrEnemies->retain();

	m_isEndGame = false;
	m_score = 0;
	m_playedTime = 0;
	m_difficulty = 0;

	m_labelScore = CCLabelBMFont::create("0", "Mia_64.fnt");
	//m_labelScore->setScale(48.0f/64);
	m_labelScore->setPosition(ccp(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - m_labelScore->getContentSize().height));
	this->addChild(m_labelScore, 10);

	m_player = Ship::create();
	m_player->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	this->addChild(m_player);

	CCString* s = CCString::createWithFormat("HP: %d", m_player->getHp());
	m_labelHp = CCLabelBMFont::create(s->getCString(), "Mia_64.fnt");
	//m_labelHp->setScale(48.0f/64);
	m_labelHp->setPosition(ccp(origin.x + m_labelHp->getContentSize().width/2,
		origin.y + visibleSize.height - m_labelHp->getContentSize().height));
	this->addChild(m_labelHp, 10);

	m_timeToGenerateEnemy = G_DEFAULT_TIME_TO_GENERATE_ENEMY;
	this->schedule(schedule_selector(ObjectLayer::ScheduleGenerateEnemy), m_timeToGenerateEnemy);
	
	m_EffectLayer = EffectLayer::create();
	this->addChild(m_EffectLayer, 10);
	//////////////////////////////////////////////////////////////////////////
	this->schedule(schedule_selector(ObjectLayer::ScheduleCheckCollision), CCDirector::sharedDirector()->getAnimationInterval());
	this->scheduleUpdate();

	//pixel check collision
	_rt  = CCRenderTexture::create(visibleSize.width, visibleSize.height);
	_rt->retain();
	_rt->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	_rt->setVisible(false);

    return true;
}

bool ObjectLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	m_lastPoint = pTouch->getLocation();
	return true;
}

void ObjectLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint curPoint = pTouch->getLocation();

	float dx = curPoint.x - m_lastPoint.x;
	float dy = curPoint.y - m_lastPoint.y;

	m_player->setPosition(m_player->getPositionX() + dx, m_player->getPositionY() + dy);
	m_lastPoint = curPoint;
}

void ObjectLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
}

//schedule generate enemy
void ObjectLayer::ScheduleGenerateEnemy( float dt )
{
	m_difficulty = m_score;
	int movetype = G_MOVE_STRAINGH;

	Enemy* enemy = Enemy::create(m_difficulty, movetype);
	m_arrEnemies->addObject(enemy);
	this->addChild(enemy);
}

void ObjectLayer::update( float delta )
{
	if (m_player->getHp() <= 0 && m_isEndGame == false)
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		this->unschedule(schedule_selector(ObjectLayer::ScheduleCheckCollision));
		this->unschedule(schedule_selector(ObjectLayer::ScheduleGenerateEnemy));
		this->unscheduleUpdate();
		this->setTouchEnabled(false);
		
		CCSequence* sequence = CCSequence::create(
			CCDelayTime::create(1),
			CCCallFunc::create(this, callfunc_selector(ObjectLayer::AfterDeadEffectCallback)),
			NULL
		);

		this->runAction(sequence);

		m_isEndGame = true;
	}

	//////////////////////////////////////////////////////////////////////////
	m_playedTime += delta;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCObject* it = NULL;

	int enemyCounter = 0;
	
	CCARRAY_FOREACH(m_arrEnemies, it)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(it);
	
		if (NULL != enemy)
		{
			enemyCounter++;

			//dead
			if (enemy->getHp() <= 0)
			{
				m_arrEnemies->removeObject(enemy);

				//score
				m_score += enemy->getDamage();
				CCString* sscore = CCString::createWithFormat("%d", m_score);
				m_labelScore->setString(sscore->getCString());

				DataManager::GetInstance()->SetCurrentHighScore(m_score);
			}

			//out of screen
			if (enemy->getPositionY() < - enemy->boundingBox().size.height)
			{
				this->removeChild(enemy);
				m_arrEnemies->removeObject(enemy);
			}
		}
	}
}

//check collision every frame
void ObjectLayer::ScheduleCheckCollision(float dt)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCObject* it1 = NULL;

	//Enemy -----------VS------------- Player
	CCARRAY_FOREACH(m_arrEnemies, it1)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(it1);
		if (NULL != enemy)
		{
			CCSprite* sprEnemy = CCSprite::createWithTexture(enemy->getSprite()->getTexture());
			CCSprite* sprPlayer = CCSprite::createWithTexture(m_player->getSprite()->getTexture());
			sprEnemy->setPosition(enemy->getPosition());
			sprPlayer->setPosition(m_player->getPosition());

			if (CollisionDetection::GetInstance()->areTheSpritesColliding(sprEnemy, sprPlayer, true, _rt))
			{
				AudioManager::sharedAudioManager()->PlayEffect("explosion.wav");
				
				m_player->HitBullet(enemy->getDamage());
				enemy->HitBullet(1000);

				CCString* s = CCString::createWithFormat("HP: %d", (m_player->getHp() > 0) ? m_player->getHp() : 0);
				m_labelHp->setString(s->getCString());
			}
		}
	}
}

void ObjectLayer::ContinueGame()
{
	//keep:
	//	score
	//	difficulty
	//	player's Position
	//reset:
	//	player's HP

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	this->setTouchEnabled(true);
	m_isEndGame = false;
	//reset
	m_player->setVisible(true);
	m_player->Restart();
	CCString* s = CCString::createWithFormat("HP: %d", (m_player->getHp() > 0) ? m_player->getHp() : 0);
	m_labelHp->setString(s->getCString());
	m_player->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	this->schedule(schedule_selector(ObjectLayer::ScheduleGenerateEnemy), m_timeToGenerateEnemy);
	this->schedule(schedule_selector(ObjectLayer::ScheduleCheckCollision), CCDirector::sharedDirector()->getAnimationInterval());
	this->scheduleUpdate();
}

void ObjectLayer::RestartGame()
{
	//reset:
	//	difficulty (time, score)
	//	player's HP
	//	player's Position
	//	score
	//	numberBoom
	
	m_playedTime = 0;
	m_score = 0;

	m_arrEnemies->removeAllObjects();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	this->setTouchEnabled(true);
	m_isEndGame = false;
	m_player->setVisible(true);
	m_player->Restart();
	
	m_player->setPosition(ccp(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
	CCString* s = CCString::createWithFormat("HP: %d", (m_player->getHp() > 0) ? m_player->getHp() : 0);
	m_labelHp->setString(s->getCString());

	CCString* sscore = CCString::createWithFormat("%d", m_score);
	m_labelScore->setString(sscore->getCString());

	this->schedule(schedule_selector(ObjectLayer::ScheduleGenerateEnemy), m_timeToGenerateEnemy);
	this->schedule(schedule_selector(ObjectLayer::ScheduleCheckCollision), CCDirector::sharedDirector()->getAnimationInterval());
	this->scheduleUpdate();
}

void ObjectLayer::AfterDeadEffectCallback()
{
	m_player->Dead();

	MainGameScene* parent = (MainGameScene*) this->getParent();
	parent->showEndGame(m_score);
	
	//remove all enemy
	CCObject* it;
	CCARRAY_FOREACH(m_arrEnemies, it)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(it);
		if (NULL != enemy)
		{
			this->removeChild(enemy);
		}
	}

	m_arrEnemies->removeAllObjects();
}

void ObjectLayer::Pause()
{
	CCObject* it;

	//Enemy
	CCARRAY_FOREACH(m_arrEnemies, it)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(it);

		if (NULL != enemy)
		{
			enemy->pauseSchedulerAndActions();
		}
	}

	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	this->unschedule(schedule_selector(ObjectLayer::ScheduleCheckCollision));
	this->unschedule(schedule_selector(ObjectLayer::ScheduleGenerateEnemy));
	this->unscheduleUpdate();
	this->setTouchEnabled(false);
}

void ObjectLayer::Resume()
{
	CCObject* it;

	//Enemy
	CCARRAY_FOREACH(m_arrEnemies, it)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(it);

		if (NULL != enemy)
		{
			enemy->resumeSchedulerAndActions();
		}
	}

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	this->schedule(schedule_selector(ObjectLayer::ScheduleGenerateEnemy), m_timeToGenerateEnemy);
	this->schedule(schedule_selector(ObjectLayer::ScheduleCheckCollision), CCDirector::sharedDirector()->getAnimationInterval());
	this->scheduleUpdate();
	this->setTouchEnabled(true);
}
