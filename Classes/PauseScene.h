#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#pragma once
#include "cocos2d.h"

USING_NS_CC;

class PauseScene : public Layer	{
public:
	static Scene* createScene();
	virtual bool init();
	
	CREATE_FUNC(PauseScene);

	void goToMainMenuScene(Ref* sender);
	void retry(Ref* sender);
	void resume(Ref* sender);

private:
	
};

#endif //__PAUSE_SCENE_H__