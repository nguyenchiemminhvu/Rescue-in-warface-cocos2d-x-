/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#include "PlayerBullet.h"
#include "Defination.h"
#include "PhysicsBodyParser\PhysicsBodyParser.h"


PlayerBullet::PlayerBullet(Vec2 gunPosition, Layer * layer)
{
	initBullet(gunPosition, layer);
	initBulletBody();
}


PlayerBullet::~PlayerBullet()
{
	bulletSprite->removeFromParentAndCleanup(true);
}

Node * PlayerBullet::getBulletSprite()
{
	return bulletSprite;
}

PhysicsBody * PlayerBullet::getBulletBody()
{
	return bulletBody;
}

void PlayerBullet::initBullet(Vec2 gunPosition, Layer *layer)
{
	bulletSprite = Sprite::create("player_bullet.png");
	bulletSprite->setPosition(Vec2(gunPosition.x + 30, gunPosition.y));
	layer->addChild(bulletSprite);
}

void PlayerBullet::initBulletBody()
{
	//bulletBody = PhysicsBodyParser::getInstance()->bodyFormJson(bulletSprite, "player_bullet", PhysicsMaterial(999, 0, 0));
	bulletBody = PhysicsBody::createBox(bulletSprite->getContentSize());
	bulletBody->setContactTestBitmask(true);
	bulletBody->setCollisionBitmask(PLAYER_BULLET_BITMASK);
	bulletBody->setDynamic(true);

	bulletSprite->setPhysicsBody(bulletBody);
	//bulletBody->setVelocity(Vec2(1000, 0));
	bulletSprite->runAction(Sequence::create(MoveBy::create(1, Vec2(1000, 0)), NULL));
}

void PlayerBullet::removeAll()
{
	log("remove player's bullet");
	bulletSprite->removeFromParentAndCleanup(true);
	this->removeFromParentAndCleanup(true);
}
