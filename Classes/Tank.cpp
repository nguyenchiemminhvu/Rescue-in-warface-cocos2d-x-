/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#include "Tank.h"
#include "PhysicsBodyParser\PhysicsBodyParser.h"
#include "SimpleAudioEngine.h"


void Tank::spawnTank(Layer * layer)
{
	Tank *tank = new Tank(layer);
}

Tank::Tank(Layer * layer)
{
	this->layer = layer;
	visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	createTank();
	setTankAction();
}

Tank::~Tank()
{
	CC_SAFE_DELETE(tankSprite);
}

Vec2 Tank::tankPosition()
{
	return tankSprite->getPosition();
}

void Tank::createTank()
{
	tankSprite = Sprite::create("images/tank_air_defense.png");
	tankSprite->setPosition(origin.x + visibleSize.width + cocos2d::random(-100, 100),
		origin.y + GROUND_THICKNESS - tankSprite->getContentSize().height / 2);

	this->layer->addChild(tankSprite);
}

void Tank::setTankAction()
{
	auto moveLeft1 = MoveBy::create(TANK_RELOAD_DURATION, Vec2(-100, 0));
	auto launch = CallFunc::create(this, callfunc_selector(Tank::launchMissile));
	auto step1 = Sequence::create(moveLeft1, launch, NULL);

	auto moveLeft2 = MoveBy::create(TANK_RELOAD_DURATION * 2, Vec2(-200, 0));
	auto step2 = Sequence::create(moveLeft2, launch, NULL);

	auto moveLeft3 = MoveBy::create(TANK_RELOAD_DURATION * 3, Vec2(-700, 0));
	auto step3 = Sequence::create(moveLeft3, NULL);

	auto tankSequence = Sequence::create(step1, step2, step3, CallFunc::create(tankSprite, callfunc_selector(Sprite::removeFromParent)), CallFunc::create(this, callfunc_selector(Tank::removeFromParent)), NULL);
	tankSprite->runAction(tankSequence);
}

void Tank::launchMissile()
{
	tankMissile = cocos2d::Sprite::create("images/tank_ammo.png");
	tankMissile->setPosition(tankPosition());
	this->layer->addChild(tankMissile, 1000);

	//create tank missile body
	PhysicsBodyParser::getInstance()->parseJsonFile("CustomPhysicsBody.json");
	auto tankMissileBody = PhysicsBodyParser::getInstance()->bodyFormJson(tankMissile, "tank_missile", PhysicsMaterial(1, 1, 0));
	tankMissileBody->setContactTestBitmask(true);
	tankMissileBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	tankMissile->setPhysicsBody(tankMissileBody);

	//tank's missile sequence action
	aimPosition = targetPosition();
	auto missileFlying = MoveTo::create(1, aimPosition);
	auto explode = CallFunc::create(this, callfunc_selector(Tank::missileExplode));
	
	tankMissile->runAction(Sequence::create(missileFlying, explode, NULL));
}

cocos2d::Vec2 Tank::targetPosition()
{
	return cocos2d::Vec2(cocos2d::random(origin.x + 100, origin.x + 500), cocos2d::random(origin.y + GROUND_THICKNESS + 100, origin.y + visibleSize.height - 100));
}

void Tank::missileExplode()
{
	auto explosion = ParticleExplosion::createWithTotalParticles(100);
	explosion->setEmitterMode(ParticleSystem::Mode::RADIUS);
	explosion->setPosition(aimPosition);
	explosion->setStartColor(Color4F(0xff, 0, 0, 0xff));
	explosion->setEndColor(Color4F(0xff, 0x55, 0, 0xff));
	explosion->setEndRadius(300);

	auto explosionBody = PhysicsBody::createCircle(100);
	explosionBody->setDynamic(false);
	explosionBody->setContactTestBitmask(true);
	explosionBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	explosion->setPhysicsBody(explosionBody);

	explosion->runAction(Sequence::create(DelayTime::create(1), CallFunc::create(explosion, callfunc_selector(ParticleExplosion::removeFromParent)), NULL));
	
	layer->addChild(explosion);
	tankMissile->removeFromParentAndCleanup(true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/tank_sound.mp3");
}
