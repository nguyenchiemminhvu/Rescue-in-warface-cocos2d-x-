/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#ifndef __PLAYER_BULLET_H__
#define __PLAYER_BULLET_H__

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class PlayerBullet : public Node
{
public:
	PlayerBullet(Vec2 gunPosition, Layer *layer);
	virtual ~PlayerBullet();

	Node* getBulletSprite();
	PhysicsBody *getBulletBody();

	void removeAll();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	Sprite *bulletSprite;
	PhysicsBody *bulletBody;

	void initBullet(Vec2 gunPosition, Layer *layer);
	void initBulletBody();
};

#endif //__PLAYER_BULLET_H__