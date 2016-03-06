/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#pragma once
#include "cocos2d.h"

USING_NS_CC;

class SplashScene : public Layer	{
public:
	static Scene* createScene();
	virtual bool init();
	
	CREATE_FUNC(SplashScene);

private:

	Sprite *splash;

	void goToMainMenuScene(float t);
};

#endif //__SPLASH_SCENE_H__