#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#pragma once
#include "cocos2d.h"
#include "HUD.h"
#include "Player.h"

USING_NS_CC;

class GameScene : public Layer	{
public:
	static Scene* createScene();
	virtual bool init();
	
	CREATE_FUNC(GameScene);

	void goToPauseScene(Ref* sender);
	void goToGameOverScene(Ref* sender);
	void finishedGame();

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

	PhysicsWorld* physicsWorld;
	HUD* hud;
	uint16_t countFrames;

	void increaseCountFrames();
	void resetCountFrames();
	void initHUD();
	void initKeyboardListener();
	void initMouseListener();
	void initContactListener();
	void initBoundPhysicsBody();
	void initGroundPhysicsBody();

	void onKeyPressedEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void onKeyReleaseEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void onMouseMoveEvent(cocos2d::EventMouse *event);
	bool onContactBegin(PhysicsContact &contact);

	void setPhysicsWorld(PhysicsWorld* world)	{ physicsWorld = world; }
	void resetBackground();
	void resetOutdoor();
	
	void initGround();
	void initGameScene();
	void initPlayer();
	void initRainEffect();

	void spawnTank(float t);
	void spawnRangeMissile(float t);
};

#endif //__GAME_SCENE_H__