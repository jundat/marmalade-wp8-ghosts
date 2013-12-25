#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class MenuScene : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
	CREATE_FUNC(MenuScene);

	virtual void keyBackClicked();
    
    void playCallback(CCObject* pSender);
	void aboutCallback(CCObject* pSender);
	void exitCallback(CCObject* pSender);
	void soundCallback(CCObject* pSender);
};

#endif // __MENU_SCENE_H__
