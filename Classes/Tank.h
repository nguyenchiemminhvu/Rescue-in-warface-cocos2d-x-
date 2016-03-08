/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#ifndef __TANK_H__
#define __TANK_H__

#pragma once

#include "cocos2d.h"
#include "Defination.h"

USING_NS_CC;

class Tank : public Node
{
public:
	static void spawnTank(Layer *layer);

	Tank(Layer *layer);
	virtual ~Tank();

	Vec2 tankPosition();

private:

	cocos2d::Layer *layer;
	cocos2d::Sprite *tankSprite;
	cocos2d::Sprite *tankMissile;
	cocos2d::Vec2 aimPosition;

	void createTank();
	void setTankAction();

	void launchMissile();
	cocos2d::Vec2 targetPosition();
	void missileExplode();
};

#endif //__TANK_H__