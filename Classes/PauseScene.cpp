/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#include "PauseScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "Defination.h"


Scene* PauseScene::createScene()	{
	auto scene = Scene::create();
	auto layer = PauseScene::create();
	scene->addChild(layer);
	return scene;
}


bool PauseScene::init()	{
	if(!Layer::init())	{
		return false;
	}
	
	cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(true);
	initKeyboardListener();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	pauseLabel = LabelTTF::create("Game Paused", "fonts/", 30);
	pauseLabel->setScale(2);
	pauseLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + pauseLabel->getContentSize().height));
	this->addChild(pauseLabel);

	return true;
}


void PauseScene::back(Ref* sender)	{
	Director::getInstance()->popScene();
}

void PauseScene::initKeyboardListener()
{
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(PauseScene::onKeyPressedEvent, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
}

void PauseScene::onKeyPressedEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		this->back(this);
		break;
	}
}
