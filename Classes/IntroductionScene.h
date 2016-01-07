#ifndef __INTRODUCTION_SCENE_H__
#define __INTRODUCTION_SCENE_H__

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class IntroductionScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(IntroductionScene);

private:

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	Sprite *background;
	Sprite *helicopter;
	Sprite *soldier1;
	Sprite *soldier2;
	Sprite *soldier3;

	cocos2d::Sequence* helicopterComing();
	cocos2d::Sequence* helicopterLeaving();
	cocos2d::Sequence* soldiersMovement();
	void goToGameScene(float t);
};

#endif //__INTRODUCTION_SCENE_H__