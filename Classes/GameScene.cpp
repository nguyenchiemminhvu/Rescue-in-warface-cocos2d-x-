#include "GameScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"
#include "Defination.h"


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

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	background = Sprite::create("game_background.png");
	background2 = Sprite::create("game_background.png");

	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	background2->setPosition(background->getPosition().x + background->getContentSize().width,
							background->getPosition().y);

	player = Sprite::create("helicopter_transportation.png");
	player->setPosition(origin.x + player->getContentSize().width, origin.y + visibleSize.height / 2);

	this->addChild(background);
	this->addChild(background2);
	this->addChild(player);

	return true;
}

void GameScene::goToPauseScene(Ref* sender)	{
	auto pauseScene = PauseScene::createScene();
	Director::getInstance()->pushScene(pauseScene);
}


void GameScene::goToGameOverScene(Ref* sender)	{
	auto gameOverScene = GameOverScene::createScene( hud->getScore() );
	Director::getInstance()->replaceScene( gameOverScene );
}

void GameScene::update(float dt)
{
	background->setPosition(background->getPosition().x - dt * 100, background->getPosition().y);
	background2->setPosition(background->getPosition().x + background->getContentSize().width,
							 background->getPosition().y);

	if (background->getPosition().x <= origin.x - visibleSize.width / 2) {
		resetBackground();
	}
}

void GameScene::resetBackground()
{
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	background2->setPosition(background->getPosition().x + background->getContentSize().width,
		background->getPosition().y);
}
