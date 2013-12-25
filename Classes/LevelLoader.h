#pragma once

#ifndef __LEVEL_LOADER_H__
#define __LEVEL_LOADER_H__

#include "Global.h"
#include "MyMacro.h"
#include "cocos2d.h"

USING_NS_CC;

class LevelData : public CCObject {
public:
	LevelData(int score, float time) {
		m_score = score;
		m_time =  time;
	}
	static LevelData* create(int score, float time) {
		LevelData* ld = new LevelData(score, time);
		ld->autorelease();
		return ld;
	}

	const char* ToString() {
		CCString* s = CCString::createWithFormat("(%d, %f)", m_score, m_time);
		return s->getCString();
	}

	int m_score;
	float m_time;
};

class LevelLoader
{
public:
	LevelLoader(void);
	~LevelLoader(void){
		RELEASE(m_dict);
	}

	static CCString* s_levelFile;
	static LevelLoader* shareConfigLoader();

	CCDictionary* m_dict;

	LevelData* GetValue(int keyScore);

protected:
	static LevelLoader* s_instance;
};


#endif //__LEVEL_LOADER_H__