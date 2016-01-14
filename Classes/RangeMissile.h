#ifndef __RANGE_MISSILE_H__
#define __RANGE_MISSILE_H__

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class RangeMissile
{
public:
	static RangeMissile* spawnRangeMissile(cocos2d::Layer *layer);
	RangeMissile(cocos2d::Layer *layer);
	virtual ~RangeMissile();

private:
	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize;

	cocos2d::Layer *layer;
	cocos2d::Sprite *missileSprite;
	cocos2d::ParticleSun *fire;

	void createMissileSprite();
	void createParticleFire();

	Sequence * missileAction();
	Sequence * particleAction();
};

#endif //__RANGE_MISSILE_H__