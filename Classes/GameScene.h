#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#pragma once
#include "cocos2d.h"
#include "HUD.h"
#include "Player.h"
#include "PlayerBullet.h"
#include "PauseScene.h"
#include "GameOverScene.h"
#include "FinishedScene.h"
#include "Defination.h"
#include "Tank.h"
#include "RangeMissile.h"
#include "TowerDefense.h"
#include "PlayerBullet.h"
#include "Gascan.h"
#include "MiniBoss.h"
#include "BigBoss.h"

#include <vector>

USING_NS_CC;

class GameScene : public Layer	{
public:

	static Scene* createScene();
	virtual bool init();
	
	CREATE_FUNC(GameScene);

	void goToPauseScene();
	void goToGameOverScene();
	void goToFinishedScene();

	void update(float dt);

private:

	Player *player;

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	Sprite *ground;
	Sprite *ground2;
	Sprite *outdoor;
	Sprite *outdoor2;

	cocos2d::ParticleRain *rainEffect;

	PhysicsWorld *physicsWorld;
	PhysicsBody *boundBody;
	HUD* hud;
	uint16_t countFrames;
	uint16_t usedFuel;
	Gascan *gascan;

	MiniBoss *miniBoss;
	BigBoss *motherFucker;

	cocos2d::EventListenerKeyboard *keyListener;
	cocos2d::EventListenerMouse *mouseListener;
	cocos2d::EventListenerTouchOneByOne *touchListener;
	cocos2d::EventListenerPhysicsContact *contactListener;

	//////////////////////////////////////////
	// Initialize
	void increaseCountFrames();
	void resetCountFrames();
	void resetUsedFuel();
	void initHUD();
	void initKeyboardListener();
	void initMouseListener();
	void initTouchListener();
	void initContactListener();
	void initBoundPhysicsBody();
	void initGroundPhysicsBody();
	void initGround();
	void initGameScene();
	void initPlayer();
	void initRainEffect();

	//////////////////////////////////////////
	// Handle event
	void onKeyPressedEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void onKeyReleaseEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void onMouseMoveEvent(cocos2d::EventMouse *event);
	bool onTouchEventBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	bool onContactBegin(PhysicsContact &contact);
	bool onBulletContactWithMiniBossBegin1(PhysicsContact &contact);
	bool onBulletContactWithMiniBossBegin2(PhysicsContact &contact);
	bool onBulletContactWithBigBossBegin(PhysicsContact &contact);

	//////////////////////////////////////////
	// Setting background
	void setPhysicsWorld(PhysicsWorld* world)	{ physicsWorld = world; }
	void resetBackground();
	void resetOutdoor();

	///////////////////////////////////////////
	// Spawn obstacle
	void spawnTank(float t);
	void spawnRangeMissile(float t);
	void spawnTower(float t);
	void spawnPlayerBullet(float t);
	void spawnGascan(float t);

	void stopSpawnObstacle();
	void resumeSpawnObstacle();

	//////////////////////////////////////////
	// Fuel problems
	void outOfFuel();

	//////////////////////////////////////////
	// Sound effect
	void playBackgroundMusic();
	void stopBackgroundMusic();
	void resumeBackgroundMusic();

	//////////////////////////////////////////
	// Boss
	void warning();
	void createMiniBoss();
	void startMiniBoss();
	void startMiniBoss(float t);
	void createBigBoss();
	void startBigBoss();
	void startBigBoss(float t);
	void startMiniBossLoop(float t);
	void startBigBossLoop(float t);
};

#endif //__GAME_SCENE_H__