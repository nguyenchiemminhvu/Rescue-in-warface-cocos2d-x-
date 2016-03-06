/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"

USING_NS_CC;

static uint64_t finalScore;

class GameOverScene : public Layer	{
public:
	static Scene* createScene(uint64_t score);
	virtual bool init();
	
	CREATE_FUNC(GameOverScene);

	void goToMainMenuScene(Ref* sender);
	void goToGameScene(Ref* sender);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite *background;
	ui::Button *buttonRetry;
	ui::Button *buttonMenu;
	cocos2d::LabelTTF *labelGameOver;
	cocos2d::LabelTTF *labelScore;
	cocos2d::LabelTTF *labelBestScore;

	void initUserDatabase();
	void initBackground();
	void initButtons();
	void initLabel();

	void handleButtonRetryClicked(Ref *sender, ui::Widget::TouchEventType type);
	void handleButtonMenuClicked(Ref *sender, ui::Widget::TouchEventType type);
};

#endif //__GAMEOVER_SCENE_H__