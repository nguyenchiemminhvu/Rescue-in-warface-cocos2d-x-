#ifndef __TANK_H__
#define __TANK_H__

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Tank : public Node
{
public:
	static void spawnTank(Layer *layer);

	Tank(Layer *layer);
	virtual ~Tank();

	Vec2 tankPosition();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

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