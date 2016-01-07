#ifndef __PLAYER_H__
#define __PLAYER_H__

#pragma once

#include "cocos2d.h"
#include "Vector2D.h"
#include "Point2D.h"
#include "Defination.h"

USING_NS_CC;

class Player
{
public:
	Player(Layer *layer);
	virtual ~Player();

	int getPosX();
	int getPosY();
	void setPosX(int x);
	void setPosY(int y);

	void handleKeyDownEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void handleKeyReleaseEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	void update(float dt);

private:
	Point2D playerPos;
	Vector2D playerVel;
};

#endif //__PLAYER_H__