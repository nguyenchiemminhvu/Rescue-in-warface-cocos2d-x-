#ifndef __PLAYER_H__
#define __PLAYER_H__

#pragma once

#include "cocos2d.h"
#include "Vector2D.h"
#include "Defination.h"

USING_NS_CC;

class Player : public Node
{
public:

	enum PlayerProperties
	{
		FLYING_SPEED = 100
	};

	enum MovementDirection
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	Player(Layer *layer);
	virtual ~Player();

	Vec2 getPlayerGunPosition();
	void handleKeyPressedEvent(cocos2d::EventKeyboard::KeyCode keyCode);
	void handleKeyReleasedEvent(cocos2d::EventKeyboard::KeyCode keyCode);
	void move(float dt);
	void getBack();
	void lostControl();
	void update(float dt);

private:

	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize;

	bool *keys;

	Layer *layer;
	Sprite *playerSprite;
	Sprite *playerGun;
	Vec2 previousPosition;

	void loadPlayerSprite(Layer *layer);
	void loadPlayerGun(Layer *layer);
	void shiftPlayerGun();
	void initPlayerPhysicsBody();
};

#endif //__PLAYER_H__