#include "GameScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"
#include "Defination.h"
#include "Tank.h"


Scene* GameScene::createScene()	{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity( Vec2(0, 0) );

	auto layer = GameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	
	scene->addChild(layer);
	return scene;
}


bool GameScene::init()	{
	if(!Layer::init())	{
		return false;
	}

	this->scheduleUpdate();
	this->schedule(schedule_selector(GameScene::spawnTank), TANK_SPAWN_TIME);

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	background = Sprite::create("game_background.png");
	background2 = Sprite::create("game_background.png");

	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	background2->setPosition(background->getPosition().x + background->getContentSize().width,
							background->getPosition().y);

	this->addChild(background);
	this->addChild(background2);

	initPlayer();
	initHUD();
	initKeyboardListener();
	initMouseListener();

	cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(false);
	return true;
}

void GameScene::goToPauseScene(Ref* sender)	{
	auto pauseScene = PauseScene::createScene();
	Director::getInstance()->pushScene(pauseScene);
}


void GameScene::goToGameOverScene(Ref* sender)	{
	auto gameOverScene = GameOverScene::createScene();
	Director::getInstance()->replaceScene( gameOverScene );
}

void GameScene::finishedGame()
{

}

void GameScene::update(float dt)
{
	player->update(dt);

	//handle background scrolling
	background->setPosition(background->getPosition().x - dt * 100, background->getPosition().y);
	background2->setPosition(background->getPosition().x + background->getContentSize().width,
							 background->getPosition().y);

	if (background->getPosition().x <= origin.x - visibleSize.width / 2) {
		resetBackground();
	}

	//used for calculate the remaining distance 
	increaseCountFrames();
}

void GameScene::increaseCountFrames()
{
	countFrames++;

	if (countFrames >= 100) {

		resetCountFrames();
		hud->decreaseDistance();

		if (hud->getRemainingDistance() <= 0) {
			finishedGame();
		}
	}
}

void GameScene::resetCountFrames()
{
	countFrames = 0;
}

void GameScene::initHUD()
{
	countFrames = 0;
	this->hud = HUD::createHUD();
	this->addChild(hud, 500);
}

void GameScene::initKeyboardListener()
{
}

void GameScene::initMouseListener()
{
	auto mouseListener = cocos2d::EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMoveEvent, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void GameScene::onKeyPressedEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	player->handleKeyPressedEvent(keyCode, event);
}

void GameScene::onKeyReleaseEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
}

void GameScene::onMouseMoveEvent(cocos2d::EventMouse * event)
{
	player->handleMouseMoveEvent(event);
}

void GameScene::resetBackground()
{
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	background2->setPosition(background->getPosition().x + background->getContentSize().width,
							 background->getPosition().y);
}

void GameScene::initPlayer()
{
	player = new Player(this);
}

void GameScene::spawnTank(float t)
{
	Tank::spawnTank(this);
}
