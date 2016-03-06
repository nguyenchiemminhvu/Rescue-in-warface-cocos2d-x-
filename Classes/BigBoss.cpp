/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#include "BigBoss.h"
#include "PhysicsBodyParser\PhysicsBodyParser.h"


BigBoss::BigBoss(Layer *layer)
{
	started = false;
	init(layer);
}

PhysicsBody * BigBoss::getBigBossBody()
{
	return bossBody;
}

void BigBoss::init(Layer * layer)
{
	this->layer = layer;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	initBoss();
	initBulletsDirection();

	verticalFlightDistance = ((visibleSize.height - GROUND_THICKNESS) - bossSprite->getContentSize().height) / 2;
}

int BigBoss::getHealth()
{
	return health;
}

void BigBoss::decreaseHealth()
{
	if (health > 0)
		health--;
	else  {
		bossDeath();
	}
}

void BigBoss::bossDeath()
{
	health = INT_MAX;
	dead = true;
	bossBody->removeFromWorld();
	bossSprite->removeFromParentAndCleanup(true);
}

bool BigBoss::isBossDead()
{
	return dead;
}

void BigBoss::start()
{
	bossSprite->runAction(preparation());
}

bool BigBoss::isStarted()
{
	return started;
}

void BigBoss::setStarted(bool started)
{
	this->started = started;
}

void BigBoss::loopAction()
{
	auto loop = RepeatForever::create(Sequence::create(action1(), NULL));
	bossSprite->runAction(loop);
}

void BigBoss::initBoss()
{
	bossSprite = Sprite::create("enemy_upgraded.png");
	bossSprite->setPosition(Vec2(origin.x + visibleSize.width - bossSprite->getContentSize().width / 2,
								 origin.y + visibleSize.height + bossSprite->getContentSize().height * 2));

	health = 40;
	flip = false;
	dead = false;
	bossSprite->setFlipX(flip);

	bossBody = PhysicsBody::createBox(Size(bossSprite->getContentSize().width, bossSprite->getContentSize().height / 2), PHYSICSBODY_MATERIAL_DEFAULT, Vec2(0, -10));
	bossBody->setContactTestBitmask(true);
	bossBody->setCollisionBitmask(BOSS_COLLISION_BITMASK);
	bossBody->setDynamic(false);

	bossSprite->setPhysicsBody(bossBody);

	layer->addChild(bossSprite);
}

void BigBoss::initBulletsDirection()
{
	bossBulletDirection[0].x = -visibleSize.width;
	bossBulletDirection[0].y = 0;

	bossBulletDirection[1].x = -visibleSize.width;
	bossBulletDirection[1].y = visibleSize.width * sin(160.0f);

	bossBulletDirection[2].x = -visibleSize.width;
	bossBulletDirection[2].y = -visibleSize.width * sin(160.0f);
}

Sequence * BigBoss::preparation()
{
	auto moveDown = MoveBy::create(BIG_BOSS_PREPARE_DURATION, Vec2(0, (origin.y + (visibleSize.height + GROUND_THICKNESS) / 2) - bossSprite->getPositionY()));
	auto prepare = Sequence::create(moveDown, NULL);
	return prepare;
}

Sequence * BigBoss::action1()
{
	auto attack = CallFunc::create(this, callfunc_selector(BigBoss::attack));
	Sequence *action = Sequence::create(
										moveDown(), attack, moveDown(), attack,
										moveUp(), attack, moveUp(), attack,
										moveUp(), attack, moveUp(), attack,
										moveDown(), attack, moveDown(), attack,
										NULL
									   );
	return action;
}

Sequence * BigBoss::action2()
{
	auto attack = CallFunc::create(this, callfunc_selector(BigBoss::attack));
	Sequence *action = Sequence::create(
										moveUp(), attack, moveUp(), attack,
										NULL
									   );
	return nullptr;
}

Sequence * BigBoss::action3()
{
	auto attack = CallFunc::create(this, callfunc_selector(BigBoss::attack));
	Sequence *action = Sequence::create(
										moveUp(), attack, moveUp(), attack,
										NULL
									   );
	return action;
}

Sequence * BigBoss::action4()
{
	auto attack = CallFunc::create(this, callfunc_selector(BigBoss::attack));
	Sequence *action = Sequence::create(
										moveDown(), attack, moveDown(), attack,
										NULL
									   );
	return action;
}

void BigBoss::flipBoss()
{
	flip = !flip;
	bossSprite->setFlipX(flip);
}

MoveBy * BigBoss::moveUp()
{
	float duration = 2.0f;
	auto action = MoveBy::create(duration / 2, Vec2(0, verticalFlightDistance / 2));
	return action;
}

MoveBy * BigBoss::moveDown()
{
	float duration = 2.0f;
	auto action = MoveBy::create(duration / 2, Vec2(0, -verticalFlightDistance / 2));
	return action;
}

void BigBoss::attack()
{
	createBullets(Vec2(bossSprite->getPositionX() - bossSprite->getContentSize().width / 2, bossSprite->getPositionY()));
}

void BigBoss::createBullets(Vec2 position)
{
	Sprite *bullets[3];
	for (int i = 0; i < 3; i++) {
		bullets[i] = Sprite::create("bullet.png");
		bullets[i]->setPosition(position);

		auto bulletBody = PhysicsBodyParser::getInstance()->bodyFormJson(bullets[i], "bullet", PHYSICSBODY_MATERIAL_DEFAULT);
		bulletBody->setContactTestBitmask(true);
		bulletBody->setCollisionBitmask(ENEMY_BULLET_BISMASK);
		bulletBody->setDynamic(true);

		bullets[i]->setPhysicsBody(bulletBody);

		//bullets[i]'s action
		bullets[i]->runAction(createBulletAction(i));

		layer->addChild(bullets[i]);
	}
}

Sequence * BigBoss::createBulletAction(int index)
{
	auto movement = MoveBy::create(1.5, bossBulletDirection[index]);
	Sequence *action = Sequence::create(movement, NULL);
	return action;
}
