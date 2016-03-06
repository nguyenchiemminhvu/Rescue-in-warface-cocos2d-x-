#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"

USING_NS_CC;

class MainMenuScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(MainMenuScene);

private:

	Sprite *background;

	ui::Button *buttonPlay;
	ui::Button *buttonInstruction;
	ui::Button *buttonExit;

	cocos2d::LabelTTF *name;

	void handleButtonPlayClicked(Ref *sender, ui::Widget::TouchEventType type);
	void handleButtonInstructionClicked(Ref *sender, ui::Widget::TouchEventType type);
	void handleButtonExitClicked(Ref *sender, ui::Widget::TouchEventType type);

	void goToIntroductionScene(Ref* sender);
	void exitGame(Ref* sender);
};

#endif //__MAINMENU_SCENE_H__