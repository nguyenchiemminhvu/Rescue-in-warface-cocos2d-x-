/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "Defination.h"

USING_NS_CC;

class PauseScene : public Layer	{

public:
	static Scene* createScene();
	virtual bool init();
	
	CREATE_FUNC(PauseScene);

	void back(Ref* sender);

private:

	cocos2d::LabelTTF *pauseLabel;

	void initKeyboardListener();
	void onKeyPressedEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
};

#endif //__PAUSE_SCENE_H__