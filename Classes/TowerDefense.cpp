/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#include "TowerDefense.h"
#include "PhysicsBodyParser\PhysicsBodyParser.h"
#include "SimpleAudioEngine.h"


void TowerDefense::spawnTower(Layer * layer)
{
	TowerDefense *tower = new TowerDefense(layer);
}

TowerDefense::TowerDefense(Layer *layer)
{
	this->layer = layer;

	visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	createTower();
	createTowerBody();
	setTowerAction();
}


TowerDefense::~TowerDefense()
{
	CC_SAFE_DELETE(towerSprite);
}

void TowerDefense::createTower()
{
	towerSprite = Sprite::create("tower.png");
	towerSprite->setPosition(Vec2(origin.x + visibleSize.width, origin.y + GROUND_THICKNESS + 50));
	layer->addChild(towerSprite);
}

void TowerDefense::createTowerBody()
{
	auto towerBody = PhysicsBodyParser::getInstance()->bodyFormJson(towerSprite, "tower", PhysicsMaterial(999, 0, 0));
	towerBody->setDynamic(true);
	towerBody->setContactTestBitmask(true);
	towerBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	towerSprite->setPhysicsBody(towerBody);
}

void TowerDefense::setTowerAction()
{
	auto distance = visibleSize.width + towerSprite->getContentSize().width;
	auto duration = 12.0f;
	float ratio;

	auto defense = CallFunc::create(this, callfunc_selector(TowerDefense::defense));
	auto remove = CallFunc::create(towerSprite, callfunc_selector(Sprite::removeFromParent));
	auto removeAll = CallFunc::create(this, callfunc_selector(TowerDefense::removeAll));

	float randomDuration1 = random(1.0f, 3.0f);
	float randomDuration2 = random(1.0f, 3.0f);
	float randomDuration3 = random(1.0f, 3.0f);

	ratio = duration / randomDuration1;
	float randomDistance1 = distance / ratio;

	ratio = duration / randomDuration2;
	float randomDistance2 = distance / ratio;

	ratio = duration / randomDuration3;
	float randomDistance3 = distance / ratio;

	distance -= (randomDistance1 + randomDistance2 + randomDistance3);
	duration -= (randomDuration1 + randomDuration2 + randomDuration3);
	
	auto moveleft1 = MoveBy::create(randomDuration1, Vec2(-(randomDistance1), 0));
	auto moveleft2 = MoveBy::create(randomDuration2, Vec2(-(randomDistance2), 0));
	auto moveleft3 = MoveBy::create(randomDuration3, Vec2(-(randomDistance3), 0));
	auto moveleft4 = MoveBy::create(duration, Vec2(-(distance), 0));

	auto step1 = Sequence::create(moveleft1, defense, NULL);
	auto step2 = Sequence::create(moveleft2, defense, NULL);
	auto step3 = Sequence::create(moveleft3, defense, NULL);
	auto step4 = Sequence::create(moveleft4, NULL);

	auto towerActions = Sequence::create(step1, step2, step3, step4, remove, removeAll, NULL);

	towerSprite->runAction(towerActions);
}

void TowerDefense::defense()
{
	initTowerBulletDireciton();
	for (int i = 0; i < TOTAL_BULLET; i++) {
		auto bullet = createBullet();
		bullet->runAction(Sequence::create(createBulletAction(i), CallFunc::create(bullet, callfunc_selector(Sprite::removeFromParent)), NULL));
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/tower_sound.mp3");
}

void TowerDefense::initTowerBulletDireciton()
{
	towerBulletDirection[0].x = -visibleSize.width;
	towerBulletDirection[0].y = 0;

	towerBulletDirection[1].x = -visibleSize.width * cos(45);
	towerBulletDirection[1].y = visibleSize.width * sin(45);

	towerBulletDirection[2].x = visibleSize.width * cos(45);
	towerBulletDirection[2].y = visibleSize.width * sin(45);

	towerBulletDirection[3].x = visibleSize.width;
	towerBulletDirection[3].y = 0;
}

Sprite* TowerDefense::createBullet()
{
	auto bulletSprite = Sprite::create("bullet.png");
	bulletSprite->setPosition(Vec2(towerSprite->getPositionX(), towerSprite->getPositionY() + towerSprite->getContentSize().height / 3));
	layer->addChild(bulletSprite);

	PhysicsBodyParser::getInstance()->parseJsonFile("CustomPhysicsBody.json");
	auto bulletBody = PhysicsBodyParser::getInstance()->bodyFormJson(bulletSprite, "bullet", PhysicsMaterial(1, 1, 0));
	bulletBody->setDynamic(false);
	bulletBody->setContactTestBitmask(true);
	bulletBody->setCollisionBitmask(ENEMY_BULLET_BISMASK);
	bulletSprite->setPhysicsBody(bulletBody);

	return bulletSprite;
}

Sequence * TowerDefense::createBulletAction(int indexBullet)
{
	auto moveBy = MoveBy::create(TOWER_BULLET_DURATION, towerBulletDirection[indexBullet]);
	auto sequence = Sequence::create(moveBy, NULL);

	return sequence;
}

void TowerDefense::removeAll()
{
	this->removeFromParentAndCleanup(true);
}
