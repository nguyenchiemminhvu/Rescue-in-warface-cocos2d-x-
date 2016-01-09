#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GameOverScene : public Layer	{
public:
	static Scene* createScene();
	virtual bool init();
	
	CREATE_FUNC(GameOverScene);

	void goToMainMenuScene(Ref* sender);
	void goToGameScene(Ref* sender);

private:

};

#endif //__GAMEOVER_SCENE_H__