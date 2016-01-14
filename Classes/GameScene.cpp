#include "GameScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"
#include "Defination.h"
#include "Tank.h"
#include "RangeMissile.h"


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
	this->schedule(schedule_selector(GameScene::spawnRangeMissile), RANGE_MISSILE_SPAWN_DURATION);

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	initGround();
	initGameScene();
	initPlayer();
	initHUD();
	initKeyboardListener();
	initMouseListener();
	initRainEffect();
	initBoundPhysicsBody();
	initGroundPhysicsBody();
	initContactListener();
	
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

void GameScene::initContactListener()
{
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GameScene::initBoundPhysicsBody()
{
	PhysicsBody *bound = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3.0f, Vec2::ZERO);
	bound->setDynamic(false);
	this->setPhysicsBody(bound);
}

void GameScene::initGroundPhysicsBody()
{
	auto underGround = Sprite::create();
	underGround->setContentSize(Size(visibleSize.width, GROUND_THICKNESS));
	underGround->setAnchorPoint(Vec2(0, 0));
	underGround->setPosition(Vec2(0, 0));
	
	PhysicsBody *groundBody = PhysicsBody::createBox(Size(visibleSize.width, GROUND_THICKNESS), PHYSICSBODY_MATERIAL_DEFAULT, Vec2::ZERO);
	groundBody->setDynamic(false);
	groundBody->setContactTestBitmask(true);
	groundBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);

	this->addChild(underGround);
	underGround->setPhysicsBody(groundBody);
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

bool GameScene::onContactBegin(PhysicsContact & contact)
{
	auto shapeA = contact.getShapeA();
	auto shapeB = contact.getShapeB();

	auto bitmaskA = shapeA->getCollisionBitmask();
	auto bitmaskB = shapeB->getCollisionBitmask();

	if ((bitmaskA == PLAYER_COLLISTION_BITMASK && bitmaskB == OBSTACLE_COLLISION_BITMASK)
		|| (bitmaskA == OBSTACLE_COLLISION_BITMASK && bitmaskB == PLAYER_COLLISTION_BITMASK)) {

		goToGameOverScene(this);
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
	outdoor->setPosition(origin.x + visibleSize.width / 2, origin.y + GROUND_THICKNESS + outdoor->getContentSize().height / 2);
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

	outdoor->setPosition(origin.x + visibleSize.width / 2, origin.y + GROUND_THICKNESS + outdoor->getContentSize().height / 2);
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
	RangeMissile::spawnRangeMissile(this);
}