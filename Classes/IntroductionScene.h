/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#ifndef __INTRODUCTION_SCENE_H__
#define __INTRODUCTION_SCENE_H__

#pragma once

#include "cocos2d.h"
#include "Defination.h"
#include "ui\CocosGUI.h"

USING_NS_CC;

class IntroductionScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(IntroductionScene);

private:

	Sprite *background;
	Sprite *outdoor;
	Sprite *helicopter;
	Sprite *soldier1;
	Sprite *soldier2;
	Sprite *soldier3;

	ui::Button *buttonSkip;
	void handleButtonSkipClicked(Ref * sender, ui::Widget::TouchEventType type);

	cocos2d::Sequence* helicopterComing();
	void FlipHelicopter();
	cocos2d::Sequence* helicopterLeaving();
	cocos2d::Sequence* soldiersMovement();
	void goToGameScene(float t);
};

#endif //__INTRODUCTION_SCENE_H__