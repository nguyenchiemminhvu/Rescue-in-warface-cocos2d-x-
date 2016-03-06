/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include <memory>

Scene* GameScene::createScene()	{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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

	cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(false);

	this->scheduleUpdate();
	this->schedule(schedule_selector(GameScene::spawnTank), TANK_SPAWN_TIME);
	this->schedule(schedule_selector(GameScene::spawnRangeMissile), RANGE_MISSILE_SPAWN_DURATION);
	this->schedule(schedule_selector(GameScene::spawnTower), ENERGY_TOWER_SPAWN_DURATION);
	this->schedule(schedule_selector(GameScene::spawnGascan), GASCAN_SPAWN_DURATION);

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	initBoundPhysicsBody();
	initGround();
	initGameScene();
	initPlayer();
	initHUD();
	initMouseListener();
	initKeyboardListener();
	initTouchListener();
	initRainEffect();
	initGroundPhysicsBody();
	initContactListener();

	createMiniBoss();
	createBigBoss();

	playBackgroundMusic();

	return true;
}


void GameScene::goToPauseScene()	{
	auto pauseScene = PauseScene::createScene();
	Director::getInstance()->pushScene(pauseScene);
}


void GameScene::goToGameOverScene()	{
	auto gameOverScene = GameOverScene::createScene(hud->getScore());
	Director::getInstance()->replaceScene( gameOverScene );
}


void GameScene::goToFinishedScene()
{
	this->stopBackgroundMusic();
	auto finishedScene = FinishedScene::createScene(hud->getScore());
	Director::getInstance()->replaceScene(TransitionFade::create(5, finishedScene));
}


void GameScene::startMiniBoss()
{
	miniBoss->setStarted(true);
	stopSpawnObstacle();
	this->warning();
	this->scheduleOnce(schedule_selector(GameScene::startMiniBoss), MINI_BOSS_PREPARE_DURATION);
	this->scheduleOnce(schedule_selector(GameScene::startMiniBossLoop), MINI_BOSS_PREPARE_DURATION * 2);
}

void GameScene::startMiniBoss(float t)
{
	miniBoss->start();
}

void GameScene::startBigBoss()
{
	this->warning();
	this->scheduleOnce(schedule_selector(GameScene::startBigBoss), BIG_BOSS_PREPARE_DURATION);
	this->scheduleOnce(schedule_selector(GameScene::startBigBossLoop), BIG_BOSS_PREPARE_DURATION * 2);
}

void GameScene::startBigBoss(float t)
{
	motherFucker->start();
}

void GameScene::startMiniBossLoop(float t)
{
	miniBoss->loopAction();
}

void GameScene::startBigBossLoop(float t)
{
	motherFucker->loopAction();
}

void GameScene::update(float dt)
{
	player->update(dt);

	//handle ground scrolling
	ground->setPosition(ground->getPositionX() - dt * 100, ground->getPositionY());
	ground2->setPosition(ground->getPositionX() + ground->getContentSize().width,
							 ground->getPositionY());

	//handle outdoor scrolling
	outdoor->setPosition(outdoor->getPositionX() - dt * 50, outdoor->getPositionY());
	outdoor2->setPosition(outdoor->getPositionX() + outdoor->getContentSize().width,
						  outdoor->getPositionY());

	if (ground->getPosition().x <= origin.x - visibleSize.width / 2) {
		resetBackground();
	}

	if (outdoor->getPositionX() <= origin.x - visibleSize.width / 2) {
		resetOutdoor();
	}

	//used for calculate the remaining distance 
	increaseCountFrames();
}

void GameScene::increaseCountFrames()
{
	countFrames++;
	usedFuel++;

	if (usedFuel >= 200) {

		resetUsedFuel();
		hud->decreaseFuel();

		if (hud->getRemainingFuel() <= 0) {
			outOfFuel();
		}
	}

	if (countFrames >= 100) {

		resetCountFrames();
		hud->decreaseDistance();
		hud->increaseScrore(5);

		if (hud->getRemainingDistance() <= 0) {
			if (!miniBoss->isStarted())
				startMiniBoss();
		}
	}
}

void GameScene::resetCountFrames()
{
	countFrames = 0;
}

void GameScene::resetUsedFuel()
{
	usedFuel = 0;
}

void GameScene::initHUD()
{
	countFrames = 0;
	usedFuel = 0;
	this->hud = HUD::createHUD();
	this->addChild(hud, 500);
}

void GameScene::initKeyboardListener()
{
	keyListener = cocos2d::EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressedEvent, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleaseEvent, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
}

void GameScene::initMouseListener()
{
	mouseListener = cocos2d::EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMoveEvent, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void GameScene::initTouchListener()
{
	touchListener = cocos2d::EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchEventBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameScene::initContactListener()
{
	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GameScene::initBoundPhysicsBody()
{
	boundBody = PhysicsBody::createEdgeBox(Size(visibleSize.width + 20, visibleSize.height + 20), PhysicsMaterial(999, 0, 999), 5.0f, Vec2::ZERO);
	boundBody->setDynamic(false);
	boundBody->setContactTestBitmask(true);
	boundBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	this->setPhysicsBody(boundBody);
}

void GameScene::initGroundPhysicsBody()
{
	auto underGround = Sprite::create();
	underGround->setContentSize(Size(visibleSize.width, GAME_GROUND_THICKNESS));
	underGround->setAnchorPoint(Vec2(0, 0));
	underGround->setPosition(Vec2(0, 0));
	
	PhysicsBody *groundBody = PhysicsBody::createBox(Size(visibleSize.width, GAME_GROUND_THICKNESS), PHYSICSBODY_MATERIAL_DEFAULT, Vec2::ZERO);
	groundBody->setDynamic(false);
	groundBody->setContactTestBitmask(true);
	groundBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);

	this->addChild(underGround);
	underGround->setPhysicsBody(groundBody);
}

void GameScene::onKeyPressedEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		this->goToPauseScene();
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		this->spawnPlayerBullet(0);
		this->schedule(schedule_selector(GameScene::spawnPlayerBullet), 0.2);
		break;
	}

	player->handleKeyPressedEvent(keyCode);
}

void GameScene::onKeyReleaseEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		this->unschedule(schedule_selector(GameScene::spawnPlayerBullet));
		break;
	}

	player->handleKeyReleasedEvent(keyCode);
}

void GameScene::onMouseMoveEvent(cocos2d::EventMouse * event)
{
	
}

bool GameScene::onTouchEventBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	return true;
}

bool GameScene::onContactBegin(PhysicsContact & contact)
{
	auto shapeA = contact.getShapeA();
	auto shapeB = contact.getShapeB();

	auto bitmaskA = shapeA->getCollisionBitmask();
	auto bitmaskB = shapeB->getCollisionBitmask();

	if ((bitmaskA == PLAYER_BULLET_BITMASK && bitmaskB == OBSTACLE_COLLISION_BITMASK)) {
		shapeA->getBody()->getNode()->removeFromParentAndCleanup(true);
	}

	if ((bitmaskA == PLAYER_BULLET_BITMASK && bitmaskB == BOSS_COLLISION_BITMASK)) {
		shapeA->getBody()->getNode()->setVisible(false);
		shapeA->getBody()->removeFromWorld();
	}

	if ((bitmaskA == BOSS_COLLISION_BITMASK && bitmaskB == PLAYER_BULLET_BITMASK)) {
		shapeB->getBody()->getNode()->setVisible(false);
		shapeB->getBody()->removeFromWorld();
	}

	if ((bitmaskA == PLAYER_COLLISTION_BITMASK && bitmaskB == OBSTACLE_COLLISION_BITMASK)
		|| (bitmaskA == OBSTACLE_COLLISION_BITMASK && bitmaskB == PLAYER_COLLISTION_BITMASK)) {

		_eventDispatcher->removeAllEventListeners();
		goToGameOverScene();
	}

	if ((bitmaskA == PLAYER_COLLISTION_BITMASK && bitmaskB == ENEMY_BULLET_BISMASK)
		|| (bitmaskA == ENEMY_BULLET_BISMASK && bitmaskB == PLAYER_COLLISTION_BITMASK)) {

		_eventDispatcher->removeAllEventListeners();
		goToGameOverScene();
	}

	if ((bitmaskA == PLAYER_COLLISTION_BITMASK && bitmaskB == BOSS_COLLISION_BITMASK)
		|| (bitmaskA == BOSS_COLLISION_BITMASK && bitmaskB == PLAYER_COLLISTION_BITMASK)) {

		_eventDispatcher->removeAllEventListeners();
		goToGameOverScene();
	}

	if ((bitmaskA == PLAYER_COLLISTION_BITMASK && bitmaskB == GASCAN_COLLISION_BITMASK)
		|| (bitmaskA == GASCAN_COLLISION_BITMASK && bitmaskB == PLAYER_COLLISTION_BITMASK)) {

		hud->increaseScrore(10);
		gascan->removeAll();
		hud->increaseFuel(5);
		resetUsedFuel();
		CC_SAFE_FREE(gascan);
	}

	return true;
}

bool GameScene::onBulletContactWithMiniBossBegin1(PhysicsContact & contact)
{
	miniBoss->decreaseHealth1();
	if (miniBoss->isBossDead1()) {
		hud->increaseScrore(100);
	}

	if (miniBoss->isBossDead2() && miniBoss->isBossDead1()) {
		startBigBoss();
	}
	
	return true;
}

bool GameScene::onBulletContactWithMiniBossBegin2(PhysicsContact & contact)
{
	miniBoss->decreaseHealth2();
	if (miniBoss->isBossDead2()) {
		hud->increaseScrore(100);
	}

	if (miniBoss->isBossDead1() && miniBoss->isBossDead2()) {
		startBigBoss();
	}
	
	return true;
}

bool GameScene::onBulletContactWithBigBossBegin(PhysicsContact & contact)
{
	motherFucker->decreaseHealth();
	if (motherFucker->isBossDead()) {
		hud->increaseScrore(300);
	}

	if (motherFucker->isBossDead()) {
		this->runAction(Sequence::create(DelayTime::create(3), CallFunc::create(this, callfunc_selector(GameScene::goToFinishedScene)), NULL));
	}

	return true;
}

void GameScene::resetBackground()
{
	ground->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	ground2->setPosition(ground->getPosition().x + ground->getContentSize().width,
							 ground->getPosition().y);
}

void GameScene::resetOutdoor()
{
	outdoor->setPosition(origin.x + visibleSize.width / 2, origin.y + GAME_GROUND_THICKNESS + outdoor->getContentSize().height / 2);
	outdoor2->setPosition(outdoor->getPosition().x + outdoor->getContentSize().width,
						  outdoor->getPositionY());
}

void GameScene::initGround()
{
	ground = Sprite::create("game_ground.png");
	ground2 = Sprite::create("game_ground.png");

	ground->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	ground2->setPosition(ground->getPosition().x + ground->getContentSize().width,
						 ground->getPosition().y);

	this->addChild(ground);
	this->addChild(ground2);
}

void GameScene::initGameScene()
{
	outdoor = Sprite::create("game_scene.png");
	outdoor2 = Sprite::create("game_scene.png");

	outdoor->setPosition(origin.x + visibleSize.width / 2, origin.y + GAME_GROUND_THICKNESS + outdoor->getContentSize().height / 2);
	outdoor2->setPosition(outdoor->getPosition().x + outdoor->getContentSize().width,
						  outdoor->getPosition().y);

	this->addChild(outdoor, 0);
	this->addChild(outdoor2, 0);
}

void GameScene::initPlayer()
{
	player = new Player(this);
}

void GameScene::initRainEffect()
{
	rainEffect = cocos2d::ParticleRain::create();

	rainEffect->setEmitterMode(cocos2d::ParticleSystem::Mode::GRAVITY);
	rainEffect->setTotalParticles(200);
	rainEffect->setGravity(Vec2(-100, -300));

	this->addChild(rainEffect);
}

void GameScene::spawnTank(float t)
{
	Tank::spawnTank(this);
}

void GameScene::spawnRangeMissile(float t) {
	RangeMissile::spawnRangeMissile(this, player->getPlayerGunPosition().y);
}

void GameScene::spawnTower(float t)
{
	TowerDefense::spawnTower(this);
}

void GameScene::spawnPlayerBullet(float t)
{
	PlayerBullet *bullet = new PlayerBullet(player->getPlayerGunPosition(), this);

	auto body = bullet->getBulletBody();
	auto listener1 = EventListenerPhysicsContactWithBodies::create(body, miniBoss->getBossBody1());
	auto listener2 = EventListenerPhysicsContactWithBodies::create(body, miniBoss->getBossBody2());
	auto listener3 = EventListenerPhysicsContactWithBodies::create(body, motherFucker->getBigBossBody());

	listener1->onContactBegin = CC_CALLBACK_1(GameScene::onBulletContactWithMiniBossBegin1, this);
	listener2->onContactBegin = CC_CALLBACK_1(GameScene::onBulletContactWithMiniBossBegin2, this);
	listener3->onContactBegin = CC_CALLBACK_1(GameScene::onBulletContactWithBigBossBegin, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener3, this);
}

void GameScene::spawnGascan(float t)
{
	gascan = Gascan::spawnGascan(this);
}

void GameScene::stopSpawnObstacle()
{
	this->unschedule(schedule_selector(GameScene::spawnTank));
	this->unschedule(schedule_selector(GameScene::spawnRangeMissile));
	this->unschedule(schedule_selector(GameScene::spawnTower));
}

void GameScene::resumeSpawnObstacle()
{
	this->schedule(schedule_selector(GameScene::spawnTank), TANK_SPAWN_TIME);
	this->schedule(schedule_selector(GameScene::spawnRangeMissile), RANGE_MISSILE_SPAWN_DURATION);
	this->schedule(schedule_selector(GameScene::spawnTower), ENERGY_TOWER_SPAWN_DURATION);
}

void GameScene::outOfFuel()
{
	_eventDispatcher->removeEventListener(keyListener);
	player->lostControl();
}

void GameScene::playBackgroundMusic()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/background_sound.mp3", true);
}

void GameScene::stopBackgroundMusic()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void GameScene::resumeBackgroundMusic()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void GameScene::warning()
{
	hud->warning();
}

void GameScene::createMiniBoss()
{
	miniBoss = new MiniBoss(this);
}

void GameScene::createBigBoss()
{
	motherFucker = new BigBoss(this);
}
