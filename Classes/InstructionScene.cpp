/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#include "InstructionScene.h"


Scene * InstructionScene::createScene()
{
	auto scene = Scene::create();
	auto layer = InstructionScene::create();
	scene->addChild(layer);
	return scene;
}

bool InstructionScene::init()
{
	if (!Layer::init())
		return false;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	initComponents();

	return true;
}

void InstructionScene::initComponents()
{
	auto background = Sprite::create("images/main_menu_background.png");
	auto labelTitle = LabelTTF::create("Instruction", "fonts/Backslash.ttf", 70);
	auto labelW = LabelTTF::create("W: Move up", "fonts/", 50);
	auto labelS = LabelTTF::create("S: Move down", "fonts/", 50);
	auto labelA = LabelTTF::create("A: Move left", "fonts/", 50);
	auto labelD = LabelTTF::create("D: Move right", "fonts/", 50);
	auto labelSpaceBar = LabelTTF::create("Space bar: Fire weapon", "fonts/", 50);
	auto labelEsc = LabelTTF::create("Esc: Pause game", "fonts/", 50);
	auto button = ui::Button::create("images/button_back.png", "images/button_back_clicked.png");

	labelW->setAnchorPoint(Vec2(0, 1));
	labelS->setAnchorPoint(Vec2(0, 1));
	labelA->setAnchorPoint(Vec2(0, 1));
	labelD->setAnchorPoint(Vec2(0, 1));
	labelSpaceBar->setAnchorPoint(Vec2(0, 1));
	labelEsc->setAnchorPoint(Vec2(0, 1));

	background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	labelTitle->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - labelTitle->getContentSize().height));
	labelW->setPosition(Vec2(origin.x + labelTitle->getContentSize().width / 2, labelTitle->getPositionY() - labelTitle->getContentSize().height / 2));
	labelS->setPosition(Vec2(labelW->getPositionX(), labelW->getPositionY() - labelW->getContentSize().height));
	labelA->setPosition(Vec2(labelS->getPositionX(), labelS->getPositionY() - labelS->getContentSize().height));
	labelD->setPosition(Vec2(labelA->getPositionX(), labelA->getPositionY() - labelA->getContentSize().height));
	labelSpaceBar->setPosition(Vec2(labelD->getPositionX(), labelD->getPositionY() - labelD->getContentSize().height));
	labelEsc->setPosition(Vec2(labelSpaceBar->getPositionX(), labelSpaceBar->getPositionY() - labelSpaceBar->getContentSize().height));
	button->setPosition(Vec2(origin.x + visibleSize.width - button->getContentSize().width / 2,
							 origin.y + button->getContentSize().height / 2));

	labelTitle->setFontFillColor(Color3B::YELLOW);
	labelW->setFontFillColor(Color3B::GRAY);
	labelS->setFontFillColor(Color3B::GRAY);
	labelA->setFontFillColor(Color3B::GRAY);
	labelD->setFontFillColor(Color3B::GRAY);
	labelSpaceBar->setFontFillColor(Color3B::GRAY);
	labelEsc->setFontFillColor(Color3B::GRAY);

	this->addChild(background);
	this->addChild(labelTitle);
	this->addChild(labelW);
	this->addChild(labelS);
	this->addChild(labelA);
	this->addChild(labelD);
	this->addChild(labelSpaceBar);
	this->addChild(labelEsc);
	this->addChild(button);

	button->addTouchEventListener(CC_CALLBACK_2(InstructionScene::onButtonClickedEvent, this));
}

void InstructionScene::onButtonClickedEvent(Ref * sender, ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		getBack();
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void InstructionScene::getBack()
{
	cocos2d::Director::getInstance()->popScene();
}
