/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#ifndef __BIG_BOSS_H__
#define __BIG_BOSS_H__

#pragma once

#include "cocos2d.h"
#include "Defination.h"

USING_NS_CC;

class BigBoss : public Node
{
public:
	BigBoss(Layer *layer);

	PhysicsBody* getBigBossBody();

	int getHealth();
	void decreaseHealth();
	void bossDeath();
	bool isBossDead();

	void start();
	bool isStarted();
	void setStarted(bool started);

	//boss loop action
	void loopAction();

private:

	Layer *layer;

	float verticalFlightDistance;
	Vec2 bossBulletDirection[3];

	bool started;

	//boss properties
	Sprite *bossSprite;
	PhysicsBody *bossBody;
	int health;
	bool flip;
	bool dead;

	void init(Layer *layer);
	void initBoss();
	void initBulletsDirection();

	//boss action
	Sequence *preparation();
	Sequence *action1();
	Sequence *action2();
	Sequence *action3();
	Sequence *action4();

	void flipBoss();

	//boss movement
	MoveBy *moveUp();
	MoveBy *moveDown();

	//boss attack
	void attack();
	void createBullets(Vec2 position);
	Sequence * createBulletAction(int index);
};

#endif //__BIG_BOSS_H__