#ifndef __ABOUT_SCENE_H__
#define __ABOUT_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class AboutScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
	CREATE_FUNC(AboutScene);

	void menuCallback(CCObject* pSender);
	virtual void keyBackClicked();
};

#endif // __ABOUT_SCENE_H__
