#ifndef __GASCAN_H__
#define __GASCAN_H__

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Gascan : public Node
{
public:
	static Gascan* spawnGascan(cocos2d::Layer *layer);
	Gascan(cocos2d::Layer *layer);

	void init(cocos2d::Layer *layer);
	Sequence* initAction();

	void removeAll();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	Sprite *gascanSprite;
	PhysicsBody *gascanBody;
};

#endif //__GASCAN_H__