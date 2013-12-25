#include "DataManager.h"

DataManager* DataManager::_instance = 0;

DataManager* DataManager::GetInstance()
{
	if(DataManager::_instance == 0)
	{
		_instance = new DataManager();
	}

	return _instance;
}

//default = 0
int	DataManager::GetCurrenHighScore()
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey("CURRENT_HIGH_SCORE");
}


//Do not save value '0'
//Because default value is '0'
void DataManager::SetCurrentHighScore(int currentHighScore)
{
	if(currentHighScore > this->GetCurrenHighScore() ) {
		CCUserDefault::sharedUserDefault()->setIntegerForKey("CURRENT_HIGH_SCORE", currentHighScore);
		CCUserDefault::sharedUserDefault()->flush();
	}
}


