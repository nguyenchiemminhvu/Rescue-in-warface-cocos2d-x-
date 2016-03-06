#include "FinishedScene.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "MainMenuScene.h"

Scene * FinishedScene::createScene(uint64_t score)
{
	finalScore = score;

	auto scene = Scene::create();
	auto layer = FinishedScene::create();
	scene->addChild(layer);
	return scene;
}

bool FinishedScene::init()
{
	if (!Layer::init()) {
		return false;
	}

	cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(true);

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	initLabelContinue();
	initLabelInstruction();
	updateDatabase();
	showScore();
	initKeyboardEvent();

	return true;
}

void FinishedScene::updateDatabase()
{
	UserDefault *database = UserDefault::getInstance();
	if (finalScore > database->getIntegerForKey("bestscore")) {
		database->setIntegerForKey("bestscore", finalScore);
	}
	database->flush(); // save value
}

void FinishedScene::showScore()
{
	/*--------------------------------------------------*/
	auto stringScore = __String::createWithFormat("Score: %ld", finalScore);
	labelScore = LabelTTF::create(stringScore->getCString(), "fonts/Backslash.ttf", 70);
	labelScore->setColor(Color3B::WHITE);
	labelScore->setFontFillColor(Color3B::YELLOW);
	labelScore->setAnchorPoint(Vec2(0, 0));
	labelScore->setPosition(origin.x + labelScore->getContentSize().width / 4,
							origin.y + visibleSize.height / 2 + labelScore->getContentSize().height);

	/*--------------------------------------------------*/
	auto stringBestScore = __String::createWithFormat("Best Score: %ld", UserDefault::getInstance()->getIntegerForKey("bestscore"));
	labelBestScore = LabelTTF::create(stringBestScore->getCString(), "fonts/Backslash.ttf", 70);
	labelBestScore->setColor(Color3B::WHITE);
	labelBestScore->setFontFillColor(Color3B::RED);
	labelBestScore->setAnchorPoint(Vec2(0, 0));
	labelBestScore->setPosition(labelScore->getPositionX(),
								labelScore->getPositionY() - labelScore->getContentSize().height);

	/*--------------------------------------------------*/
	this->addChild(labelScore);
	this->addChild(labelBestScore);
}

void FinishedScene::initKeyboardEvent()
{
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(FinishedScene::onKeyPressedBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
}

void FinishedScene::onKeyPressedBegin(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	goToMainMenuScene();
}

void FinishedScene::goToMainMenuScene()
{
	cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(2, MainMenuScene::createScene()));
}

void FinishedScene::initLabelContinue()
{
	labelContinue = LabelTTF::create("To be continue...", "fonts/Backslash.ttf", 50);
	labelContinue->setPosition(Vec2(origin.x + visibleSize.width - labelContinue->getContentSize().width,
									origin.y + labelContinue->getContentSize().height * 2));

	this->addChild(labelContinue);
}

void FinishedScene::initLabelInstruction()
{
	labelInstruction = LabelTTF::create("Press any key to return to main menu!", "fonts/Backslash.ttf", 30);
	labelInstruction->setPosition(Vec2(labelContinue->getPositionX(), 
									   labelContinue->getPositionY() - labelContinue->getContentSize().height));
	this->addChild(labelInstruction);
}
