/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#include "MainMenuScene.h"
#include "GameScene.h"
#include "IntroductionScene.h"
#include "InstructionScene.h"


Scene* MainMenuScene::createScene()	{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);
	return scene;
}


bool MainMenuScene::init()	{
	if(!Layer::init())	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	background = Sprite::create("images/main_menu_background.png");
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	name = LabelTTF::create("Rescue in warface", "fonts/Backslash.ttf", 80);
	name->setColor(Color3B::WHITE);
	name->setFontFillColor(Color3B::YELLOW);
	name->setPosition(Vec2(origin.x + visibleSize.width / 2,
						   origin.y + visibleSize.height - name->getContentSize().height));

	buttonPlay = ui::Button::create("images/button_play.png", "images/button_play_clicked.png");
	buttonInstruction = ui::Button::create("images/button_instruction.png", "images/button_instruction_clicked.png");
	buttonExit = ui::Button::create("images/button_exit.png", "images/button_exit_clicked.png");

	buttonPlay->setPosition(Vec2(origin.x + visibleSize.width / 2,
								 origin.y + visibleSize.height / 2 + buttonPlay->getContentSize().height / 2.25));
	buttonInstruction->setPosition(Vec2(origin.x + visibleSize.width / 2,
										origin.y + visibleSize.height / 2 - buttonInstruction->getContentSize().height / 1.25));
	buttonExit->setPosition(Vec2(origin.x + visibleSize.width / 2,
								 origin.y + visibleSize.height / 2 - buttonExit->getContentSize().height * 2));

	this->addChild(background);
	this->addChild(name);
	this->addChild(buttonPlay);
	this->addChild(buttonInstruction);
	this->addChild(buttonExit);

	//button clicked listener
	buttonPlay->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::handleButtonPlayClicked, this));
	buttonInstruction->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::handleButtonInstructionClicked, this));
	buttonExit->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::handleButtonExitClicked, this));

	return true;
}


void MainMenuScene::handleButtonPlayClicked(Ref * sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;

	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;

	case cocos2d::ui::Widget::TouchEventType::ENDED:
		this->goToIntroductionScene(this);
		break;

	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	}
}


void MainMenuScene::handleButtonInstructionClicked(Ref * sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		this->goToInstructionScene(this);
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}


void MainMenuScene::handleButtonExitClicked(Ref * sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;

	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;

	case cocos2d::ui::Widget::TouchEventType::ENDED:
		this->exitGame(this);
		break;

	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	}
}


void MainMenuScene::goToIntroductionScene(Ref * sender)
{
	auto introduction = IntroductionScene::createScene();
	cocos2d::Director::getInstance()->replaceScene(introduction);
}


void MainMenuScene::goToInstructionScene(Ref * sender)
{
	auto instruction = InstructionScene::createScene();
	cocos2d::Director::getInstance()->pushScene(instruction);
}


void MainMenuScene::exitGame(Ref * sender)
{
	cocos2d::Director::getInstance()->end();
}
