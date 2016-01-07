#include "MainMenuScene.h"
#include "IntroductionScene.h"
#include "Defination.h"


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

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	background = Sprite::create("main_menu_background.png");
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	buttonPlay = ui::Button::create("button_play.png", "button_play_clicked.png");
	buttonExit = ui::Button::create("button_exit.png", "button_exit_clicked.png");

	buttonPlay->setPosition(Vec2(origin.x + visibleSize.width / 2,
								 origin.y + visibleSize.height / 2 + buttonPlay->getContentSize().height * 2));
	buttonExit->setPosition(Vec2(origin.x + visibleSize.width / 2,
								 origin.y + visibleSize.height / 2 - buttonExit->getContentSize().height * 2));

	this->addChild(background);
	this->addChild(buttonPlay);
	this->addChild(buttonExit);

	//button clicked listener
	buttonPlay->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::handleButtonPlayClicked, this));
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

void MainMenuScene::exitGame(Ref * sender)
{
	cocos2d::Director::getInstance()->end();
}
