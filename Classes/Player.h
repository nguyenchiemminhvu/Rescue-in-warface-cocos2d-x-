#ifndef __PLAYER_H__
#define __PLAYER_H__

#pragma once

#include "cocos2d.h"
#include "Vector2D.h"
#include "Defination.h"

USING_NS_CC;

class Player
{
public:

	Player(Layer *layer);
	virtual ~Player();

	void handleKeyPressedEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void handleKeyReleaseEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void handleMouseMoveEvent(cocos2d::EventMouse *event);

	void update(float dt);

private:

	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize;
	cocos2d::Rect activitiesArea;

	Vector2D playerCurrentVelocity;
	Vector2D mousePosition;

	Sprite *playerSprite;
	cocos2d::Vec2 playerPrePosition;
	
	void loadPlayerSprite(Layer *layer);
	void limitedPlayerArea();
	void initPlayerVelocity();
	float approachMousePosition(float separation, float dt);
};

#endif //__PLAYER_H__