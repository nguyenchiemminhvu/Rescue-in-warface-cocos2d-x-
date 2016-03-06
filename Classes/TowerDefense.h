/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#ifndef __TOWER_DEFENSE_H__
#define __TOWER_DEFENSE_H__

#pragma once

#include "cocos2d.h"
#include "Defination.h"

USING_NS_CC;

class TowerDefense : public Node
{
public:

	static void spawnTower(Layer *layer);

	TowerDefense(Layer *layer);
	virtual ~TowerDefense();

private:
	cocos2d::Layer *layer;

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	
	cocos2d::Sprite *towerSprite;
	Vec2 towerBulletDirection[TOTAL_BULLET];

	void createTower();
	void createTowerBody();
	void setTowerAction();

	void defense();
	void initTowerBulletDireciton();
	Sprite* createBullet();
	Sequence* createBulletAction(int indexBullet);

	void removeAll();
};

#endif //__TOWER_DEFENSE_H__