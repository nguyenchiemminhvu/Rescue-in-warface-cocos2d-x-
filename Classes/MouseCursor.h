#ifndef __MOUSE_CURSOR_H__
#define __MOUSE_CURSOR_H__

#pragma once

#include "cocos2d.h"

USING_NS_CC;

class MouseCursor : public Node
{
public:
	MouseCursor(Layer *layer);
	~MouseCursor();
	void setPosition(Vec2 position);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite *crosshair;

	void initCrosshairCursor();

};

#endif //__MOUSE_CURSOR_H__