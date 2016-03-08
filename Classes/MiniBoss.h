/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#ifndef __MINI_BOSS_H__
#define __MINI_BOSS_H__

#pragma once

#include "cocos2d.h"
#include "Defination.h"

USING_NS_CC;

class MiniBoss : public Node
{
public:

	enum MiniBossStates
	{
		MINI_BOSS_ALIVE,
		MINI_BOSS_DEAD
	};

	MiniBoss(Layer *layer);
	
	void setCurrentState(MiniBossStates state);
	int getCurrentState();

	PhysicsBody *getBossBody1();
	PhysicsBody *getBossBody2();
	int getHealth1();
	int getHealth2();
	void decreaseHealth1();
	void decreaseHealth2();
	void bossDeath1();
	void bossDeath2();
	bool isBossDead1();
	bool isBossDead2();

	void start();
	bool isStarted();
	void setStarted(bool started);

	//boss loop action
	void loopAction();

private:

	float verticalFlightDistance;
	float horizontalFlightDistance;

	Layer *layer;
	bool started;
	int state;

	//boss1 properties
	Sprite *bossSprite1;
	PhysicsBody *bossBody1;
	int health1;
	bool flip1;
	bool dead1;

	//boss2 properties
	Sprite *bossSprite2;
	PhysicsBody *bossBody2;
	int health2;
	bool flip2;
	bool dead2;

	void init(Layer *layer);
	void initMiniBoss1();
	void initMiniBoss2();

	//boss action
	Sequence *preparation1();
	Sequence *preparation2();
	
	Sequence *action1_1();
	Sequence *action1_2();
	Sequence *action2_1();
	Sequence *action2_2();

	void flipBoss1();
	void flipBoss2();

	//boss movement
	MoveBy *moveUp();
	MoveBy *moveDown();
	MoveBy *moveLeft();
	MoveBy *moveRight();

	//boss attack
	void attack1_1();
	void attack1_2();
	void attack2_1();
	void attack2_2();

	void createBullet(Vec2 position, bool leftToRight = true);
};

#endif //__MINI_BOSS_H__