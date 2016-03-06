/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#include "MouseCursor.h"



void MouseCursor::setPosition(Vec2 position)
{
	crosshair->setPosition(position);
}

MouseCursor::MouseCursor(Layer *layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	crosshair = Sprite::create("cross_hair_cursor.png");
	crosshair->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	layer->addChild(crosshair);
}


MouseCursor::~MouseCursor()
{
}
