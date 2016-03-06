#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "Defination.h"


Scene* GameOverScene::createScene(uint64_t score)	{

	finalScore = score;

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

	initUserDatabase();
	initBackground();
	initButtons();
	initLabel();

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

void GameOverScene::initUserDatabase()
{
	UserDefault *database = UserDefault::getInstance();
	if (finalScore > database->getIntegerForKey("bestscore")) {
		database->setIntegerForKey("bestscore", finalScore);
	}
	database->flush(); // save value
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

	buttonRetry->setPosition(Vec2(origin.x + visibleSize.width / 2, 
							      origin.y + visibleSize.height / 2 - buttonRetry->getContentSize().height / 2));
	buttonMenu->setPosition(Vec2(origin.x + visibleSize.width / 2, 
								 origin.y + visibleSize.height / 2 - buttonMenu->getContentSize().height * 2));

	this->addChild(buttonRetry);
	this->addChild(buttonMenu);

	buttonRetry->addTouchEventListener(CC_CALLBACK_2(GameOverScene::handleButtonRetryClicked, this));
	buttonMenu->addTouchEventListener(CC_CALLBACK_2(GameOverScene::handleButtonMenuClicked, this));
}

void GameOverScene::initLabel()
{
	/*--------------------------------------------------*/
	labelGameOver = LabelTTF::create("Game Over", "fonts/Backslash.ttf", 50);
	labelGameOver->setColor(Color3B(0xff, 0xff, 0));
	labelGameOver->setScale(3);
	labelGameOver->setPosition(Vec2(origin.x + visibleSize.width / 2, 
									origin.y + visibleSize.height - labelGameOver->getContentSize().height * 2));

	/*--------------------------------------------------*/
	auto stringScore = __String::createWithFormat("Score: %ld", finalScore);
	labelScore = LabelTTF::create(stringScore->getCString(), "fonts/Backslash.ttf", 50);
	labelScore->setColor(Color3B::WHITE);
	labelScore->setFontFillColor(Color3B::YELLOW);
	labelScore->setAnchorPoint(Vec2(0, 0));
	labelScore->setPosition(origin.x + labelScore->getContentSize().width / 4, 
							origin.y + visibleSize.height / 2 + labelScore->getContentSize().height);

	/*--------------------------------------------------*/
	auto stringBestScore = __String::createWithFormat("Best Score: %ld", UserDefault::getInstance()->getIntegerForKey("bestscore"));
	labelBestScore = LabelTTF::create(stringBestScore->getCString(), "fonts/Backslash.ttf", 50);
	labelBestScore->setColor(Color3B::WHITE);
	labelBestScore->setFontFillColor(Color3B::RED);
	labelBestScore->setAnchorPoint(Vec2(0, 0));
	labelBestScore->setPosition(labelScore->getPositionX(),
								labelScore->getPositionY() - labelScore->getContentSize().height);

	this->addChild(labelGameOver, 500);
	this->addChild(labelScore, 500);
	this->addChild(labelBestScore, 500);
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
