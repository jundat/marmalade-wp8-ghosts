
#ifndef __DATA_MANAGER__
#define __DATA_MANAGER__

#include "cocos2d.h"
USING_NS_CC;

class DataManager
{
private:
	DataManager(){}
	static DataManager *_instance;

public:
	~DataManager(){}
	static DataManager* GetInstance();

	int		GetCurrenHighScore();
	void	SetCurrentHighScore(int currentLevel);
};
#endif
