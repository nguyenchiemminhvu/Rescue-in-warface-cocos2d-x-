/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#include "Gascan.h"
#include "Defination.h"
#include "PhysicsBodyParser\PhysicsBodyParser.h"


Gascan * Gascan::spawnGascan(cocos2d::Layer * layer)
{
	return new Gascan(layer);
}

Gascan::Gascan(cocos2d::Layer * layer)
{
	init(layer);
}

void Gascan::init(cocos2d::Layer *layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	gascanSprite = Sprite::create("images/gascan.png");
	gascanSprite->setPositionY(origin.y + visibleSize.height + gascanSprite->getContentSize().height);
	gascanSprite->setPositionX(origin.x + (visibleSize.width / 4) + random(0.0f, (visibleSize.width / 2)));

	//gascanBody = PhysicsBodyParser::getInstance()->bodyFormJson(gascanSprite, "gascan", PhysicsMaterial(1, 0, 0));
	gascanBody = PhysicsBody::createBox(gascanSprite->getContentSize());
	gascanBody->setContactTestBitmask(true);
	gascanBody->setCollisionBitmask(GASCAN_COLLISION_BITMASK);
	gascanSprite->setPhysicsBody(gascanBody);

	gascanSprite->runAction(initAction());

	layer->addChild(gascanSprite);
}

Sequence * Gascan::initAction()
{
	auto moveDown = MoveBy::create(GASCAN_FALLING_DURATION, Vec2(0, -visibleSize.height + GROUND_THICKNESS));
	auto remove = CallFunc::create(this, callfunc_selector(Gascan::removeAll));

	auto sequence = Sequence::create(moveDown, remove, NULL);
	return sequence;
}

void Gascan::removeAll()
{
	gascanSprite->removeFromParentAndCleanup(true);
}

