#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "Defination.h"


Scene* GameOverScene::createScene()	{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}


bool GameOverScene::init()	{
	if(!Layer::init())	{
		return false;
	}
	
	cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(true);

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	initBackground();
	initButtons();

	return true;
}


void GameOverScene::goToMainMenuScene(Ref* sender)	{
	auto menuScene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene( TransitionFade::create(TRANSITION_TIME, menuScene) );
}


void GameOverScene::goToGameScene(Ref* sender)	{
	auto gameScene = GameScene::createScene();
	Director::getInstance()->replaceScene(gameScene);
}

void GameOverScene::initBackground()
{
	background = Sprite::create("main_menu_background.png");
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	this->addChild(background);
}

void GameOverScene::initButtons()
{
	buttonRetry = cocos2d::ui::Button::create("button_retry.png", "button_retry_clicked.png");
	buttonMenu = cocos2d::ui::Button::create("button_menu.png", "button_menu_clicked.png");

	buttonRetry->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + buttonRetry->getContentSize().height));
	buttonMenu->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - buttonMenu->getContentSize().height));

	this->addChild(buttonRetry);
	this->addChild(buttonMenu);

	buttonRetry->addTouchEventListener(CC_CALLBACK_2(GameOverScene::handleButtonRetryClicked, this));
	buttonMenu->addTouchEventListener(CC_CALLBACK_2(GameOverScene::handleButtonMenuClicked, this));
}

void GameOverScene::handleButtonRetryClicked(Ref *sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;

	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;

	case cocos2d::ui::Widget::TouchEventType::ENDED:
		this->goToGameScene(this);
		break;

	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	}
}

void GameOverScene::handleButtonMenuClicked(Ref *sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;

	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;

	case cocos2d::ui::Widget::TouchEventType::ENDED:
		this->goToMainMenuScene(this);
		break;

	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	}
}
