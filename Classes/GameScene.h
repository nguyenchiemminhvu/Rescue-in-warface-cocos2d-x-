#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#pragma once
#include "cocos2d.h"
#include "HUD.h"

USING_NS_CC;

class GameScene : public Layer	{
public:
	static Scene* createScene();
	virtual bool init();
	
	CREATE_FUNC(GameScene);

	void goToPauseScene(Ref* sender);
	void goToGameOverScene(Ref* sender);

	void update(float dt);

private:

	Sprite *player;

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	Sprite *background;
	Sprite *background2;

	PhysicsWorld* physicsWorld;
	HUD* hud;

	void setPhysicsWorld(PhysicsWorld* world)	{ physicsWorld = world; }
	void resetBackground();
};

#endif //__GAME_SCENE_H__