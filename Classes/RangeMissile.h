/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#ifndef __RANGE_MISSILE_H__
#define __RANGE_MISSILE_H__

#pragma once

#include "cocos2d.h"
#include "Defination.h"

USING_NS_CC;

class RangeMissile : public Node
{
public:
	static RangeMissile* spawnRangeMissile(cocos2d::Layer *layer, float playerPositionY);
	RangeMissile(cocos2d::Layer *layer, float playerPositionY);
	virtual ~RangeMissile();

private:

	cocos2d::Layer *layer;
	cocos2d::Sprite *missileSprite;
	cocos2d::ParticleSun *fire;

	void createMissileSprite(float playerPositionY);
	void createParticleFire();
	void createMissileBody();

	Sequence * missileAction();
	Sequence * particleAction();

	void removeAll();
};

#endif //__RANGE_MISSILE_H__