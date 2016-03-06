/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#include "MiniBoss.h"
#include "PhysicsBodyParser\PhysicsBodyParser.h"


MiniBoss::MiniBoss(Layer *layer)
{
	started = false;
	state = MINI_BOSS_ALIVE;
	init(layer);
}

void MiniBoss::setCurrentState(MiniBossStates state)
{
	this->state = state;
}

int MiniBoss::getCurrentState()
{
	return state;
}

PhysicsBody * MiniBoss::getBossBody1()
{
	return bossBody1;
}

PhysicsBody * MiniBoss::getBossBody2()
{
	return bossBody2;
}

int MiniBoss::getHealth1()
{
	return health1;
}

int MiniBoss::getHealth2()
{
	return health2;
}

void MiniBoss::decreaseHealth1()
{
	if (health1 > 0) {
		health1--;
	}
	else  {
		bossDeath1();
	}
}

void MiniBoss::decreaseHealth2()
{
	if (health2 > 0) {
		health2--;
	}
	else   {
		bossDeath2();
	}
}

void MiniBoss::bossDeath1()
{
	health1 = INT_MAX;
	dead1 = true;
	bossBody1->removeFromWorld();
	bossSprite1->removeFromParentAndCleanup(true);

	if (dead2)
		setCurrentState(MiniBossStates::MINI_BOSS_DEAD);
}

void MiniBoss::bossDeath2()
{
	health2 = INT_MAX;
	dead2 = true;
	bossBody2->removeFromWorld();
	bossSprite2->removeFromParentAndCleanup(true);

	if (dead1)
		setCurrentState(MiniBossStates::MINI_BOSS_DEAD);
}

bool MiniBoss::isBossDead1()
{
	return dead1;
}

bool MiniBoss::isBossDead2()
{
	return dead2;
}

void MiniBoss::start()
{
	bossSprite1->runAction(preparation1());
	bossSprite2->runAction(preparation2());
}

bool MiniBoss::isStarted()
{
	return started;
}

void MiniBoss::setStarted(bool started)
{
	this->started = started;
}

void MiniBoss::init(Layer *layer)
{
	this->layer = layer;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	initMiniBoss1();
	initMiniBoss2();

	verticalFlightDistance = ((visibleSize.height - GROUND_THICKNESS) - bossSprite1->getContentSize().height) / 2;
	horizontalFlightDistance = visibleSize.width - bossSprite1->getContentSize().width;
}

void MiniBoss::initMiniBoss1()
{
	bossSprite1 = Sprite::create("enemy.png");
	bossSprite1->setPosition(Vec2(origin.x + bossSprite1->getContentSize().width / 2,
								  origin.y + visibleSize.height + bossSprite1->getContentSize().height));
	health1 = 50;
	dead1 = false;
	flip1 = true;
	bossSprite1->setFlipX(flip1);

	//boss1 body
	bossBody1 = PhysicsBody::createBox(Size(bossSprite1->getContentSize().width, bossSprite1->getContentSize().height / 2));
	bossBody1->setContactTestBitmask(true);
	bossBody1->setCollisionBitmask(BOSS_COLLISION_BITMASK);
	bossBody1->setDynamic(false);
	bossSprite1->setPhysicsBody(bossBody1);

	layer->addChild(bossSprite1);
}

void MiniBoss::initMiniBoss2()
{
	bossSprite2 = Sprite::create("enemy.png");
	bossSprite2->setPosition(Vec2(origin.x + visibleSize.width - bossSprite1->getContentSize().width / 2, 
								  origin.y + visibleSize.height + bossSprite1->getContentSize().height));
	health2 = 50;
	dead2 = false;
	flip2 = false;
	bossSprite2->setFlipX(flip2);

	//boss2 body
	bossBody2 = PhysicsBody::createBox(Size(bossSprite2->getContentSize().width, bossSprite2->getContentSize().height / 2));
	bossBody2->setContactTestBitmask(true);
	bossBody2->setCollisionBitmask(BOSS_COLLISION_BITMASK);
	bossBody2->setDynamic(false);
	bossSprite2->setPhysicsBody(bossBody2);

	layer->addChild(bossSprite2);
}

Sequence * MiniBoss::preparation1()
{
	auto moveDown = MoveBy::create(MINI_BOSS_PREPARE_DURATION, Vec2(0, (origin.y + (visibleSize.height + GROUND_THICKNESS) / 2) - bossSprite1->getPositionY()));
	auto action = Sequence::create(moveDown, NULL);
	return action;
}

Sequence * MiniBoss::preparation2()
{
	auto moveDown = MoveBy::create(MINI_BOSS_PREPARE_DURATION, Vec2(0, (origin.y + (visibleSize.height + GROUND_THICKNESS) / 2) - bossSprite2->getPositionY()));
	auto action = Sequence::create(moveDown, NULL);
	return action;
}

Sequence * MiniBoss::action1_1()
{
	auto flip = CallFunc::create(this, callfunc_selector(MiniBoss::flipBoss1));
	auto attack1 = CallFunc::create(this, callfunc_selector(MiniBoss::attack1_1));
	auto attack2 = CallFunc::create(this, callfunc_selector(MiniBoss::attack1_2));

	Sequence *action = Sequence::create(
										moveUp(), attack1, moveUp(), attack1, moveUp(),
										moveRight(), flip,
										moveDown(), attack2, moveDown(), attack2, moveDown(),
										NULL
									   );
	return action;
}

Sequence * MiniBoss::action1_2()
{
	auto flip = CallFunc::create(this, callfunc_selector(MiniBoss::flipBoss1));
	auto attack1 = CallFunc::create(this, callfunc_selector(MiniBoss::attack1_2));
	auto attack2 = CallFunc::create(this, callfunc_selector(MiniBoss::attack1_1));

	Sequence *action = Sequence::create(
										moveDown(), attack1, moveDown(), attack1, moveDown(),
										moveLeft(), flip,
										moveUp(), attack2, moveUp(), attack2, moveUp(),
										NULL
									   );
	return action;
}

Sequence * MiniBoss::action2_1()
{
	auto flip = CallFunc::create(this, callfunc_selector(MiniBoss::flipBoss2));
	auto attack1 = CallFunc::create(this, callfunc_selector(MiniBoss::attack2_1));
	auto attack2 = CallFunc::create(this, callfunc_selector(MiniBoss::attack2_2));

	Sequence *action = Sequence::create(
										moveDown(), attack1, moveDown(), attack1, moveDown(),
										moveLeft(), flip,
										moveUp(), attack2, moveUp(), attack2, moveUp(),
										NULL
									   );
	return action;
}

Sequence * MiniBoss::action2_2()
{
	auto flip = CallFunc::create(this, callfunc_selector(MiniBoss::flipBoss2));
	auto attack1 = CallFunc::create(this, callfunc_selector(MiniBoss::attack2_2));
	auto attack2 = CallFunc::create(this, callfunc_selector(MiniBoss::attack2_1));

	Sequence *action = Sequence::create(
										moveUp(), attack1, moveUp(), attack1, moveUp(),
										moveRight(), flip,
										moveDown(), attack2, moveDown(), attack2, moveDown(),
										NULL
									   );
	return action;
}

void MiniBoss::flipBoss1()
{
	flip1 = !flip1;
	bossSprite1->setFlipX(flip1);
}

void MiniBoss::flipBoss2()
{
	flip2 = !flip2;
	bossSprite2->setFlipX(flip2);
}

MoveBy * MiniBoss::moveUp()
{
	float duration = 2.0f;
	auto action = MoveBy::create(duration / 3, Vec2(0, verticalFlightDistance / 3));
	return action;
}

MoveBy * MiniBoss::moveDown()
{
	float duration = 2.0f;
	auto action = MoveBy::create(duration / 3, Vec2(0, -verticalFlightDistance / 3));
	return action;
}

MoveBy * MiniBoss::moveLeft()
{
	float duration = 3;
	auto action = MoveBy::create(duration, Vec2(-horizontalFlightDistance, 0));
	return action;
}

MoveBy * MiniBoss::moveRight()
{
	float duration = 3;
	auto action = MoveBy::create(duration, Vec2(horizontalFlightDistance, 0));
	return action;
}

void MiniBoss::attack1_1()
{
	createBullet(Vec2(bossSprite1->getPositionX(), bossSprite1->getPositionY()), true);
}

void MiniBoss::attack1_2()
{
	createBullet(Vec2(bossSprite1->getPositionX(), bossSprite1->getPositionY()), false);
}

void MiniBoss::attack2_1()
{
	createBullet(Vec2(bossSprite2->getPositionX(), bossSprite2->getPositionY()), false);
}

void MiniBoss::attack2_2()
{
	createBullet(Vec2(bossSprite2->getPositionX(), bossSprite2->getPositionY()), true);
}

void MiniBoss::createBullet(Vec2 position, bool leftToRight)
{
	auto bullet = Sprite::create("bullet.png");
	bullet->setPosition(position);

	auto bulletBody = PhysicsBodyParser::getInstance()->bodyFormJson(bullet, "bullet", PHYSICSBODY_MATERIAL_DEFAULT);
	bulletBody->setContactTestBitmask(true);
	bulletBody->setCollisionBitmask(ENEMY_BULLET_BISMASK);
	bulletBody->setDynamic(true);

	bullet->setPhysicsBody(bulletBody);

	//bullet action
	MoveBy *movement;
	if (leftToRight)
		movement = MoveBy::create(1, Vec2(horizontalFlightDistance, 0));
	else
		movement = MoveBy::create(1, Vec2(-horizontalFlightDistance, 0));

	auto remove = CallFunc::create(bullet, callfunc_selector(Sprite::removeFromParent));
	bullet->runAction(Sequence::create(movement, remove, NULL));

	layer->addChild(bullet);
}

void MiniBoss::loopAction()
{
	auto loopAction1 = RepeatForever::create(Sequence::create(action1_1(), action1_2(), NULL));
	auto loopAction2 = RepeatForever::create(Sequence::create(action2_1(), action2_2(), NULL));

	bossSprite1->runAction(loopAction1);
	bossSprite2->runAction(loopAction2);
}
