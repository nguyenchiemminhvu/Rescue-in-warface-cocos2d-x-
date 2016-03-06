#ifndef __FINISHED_SCENE_H__
#define __FINISHED_SCENE_H__

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class FinishedScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(FinishedScene);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::LabelTTF *label;

	void initLabel();
};

#endif //__FINISHED_SCENE_H__
