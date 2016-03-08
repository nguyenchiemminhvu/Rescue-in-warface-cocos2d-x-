/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#ifndef __FINISHED_SCENE_H__
#define __FINISHED_SCENE_H__

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class FinishedScene : public Layer
{
public:
	static Scene* createScene(uint64_t score);
	virtual bool init();

	CREATE_FUNC(FinishedScene);

private:

	cocos2d::LabelTTF *labelContinue;
	cocos2d::LabelTTF *labelInstruction;
	cocos2d::LabelTTF *labelScore;
	cocos2d::LabelTTF *labelBestScore;

	void initLabelContinue();
	void initLabelInstruction();
	void updateDatabase();
	void showScore();
	void initKeyboardEvent();

	void onKeyPressedBegin(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void goToMainMenuScene();
};

#endif //__FINISHED_SCENE_H__
