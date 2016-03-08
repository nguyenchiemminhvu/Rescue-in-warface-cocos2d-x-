/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#ifndef __INSTRUCTION_SCENE_H__
#define __INSTRUCTION_SCENE_H__

#pragma once

#include "cocos2d.h"
#include "Defination.h"
#include "ui\CocosGUI.h"

USING_NS_CC;

class InstructionScene : public Layer
{
public:
	
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(InstructionScene);

private:

	void initComponents();

	void onButtonClickedEvent(Ref *sender, ui::Widget::TouchEventType type);
	void getBack();
};

#endif //__INSTRUCTION_SCENE_H__