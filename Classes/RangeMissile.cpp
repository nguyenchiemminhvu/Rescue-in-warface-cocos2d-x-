#include "RangeMissile.h"
#include "Defination.h"



RangeMissile * RangeMissile::spawnRangeMissile(cocos2d::Layer *layer)
{
	return new RangeMissile(layer);
}

RangeMissile::RangeMissile(cocos2d::Layer *layer)
{
	this->layer = layer;

	origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	this->createMissileSprite();
	this->createParticleFire();

	missileSprite->runAction(missileAction());
	fire->runAction(particleAction());
}


RangeMissile::~RangeMissile()
{
	CC_SAFE_DELETE(missileSprite);
}

void RangeMissile::createMissileSprite()
{
	missileSprite = Sprite::create("missile.png");

	missileSprite->setAnchorPoint(Vec2(1, 0.5));
	missileSprite->setPosition(Vec2(origin.x, random(origin.y + GROUND_THICKNESS + missileSprite->getContentSize().height, origin.y + visibleSize.height)));

	layer->addChild(missileSprite);
}

void RangeMissile::createParticleFire()
{
	fire = cocos2d::ParticleSun::create();
	
	fire->setAnchorPoint(Vec2(1, 0.5));
	fire->setPosition(Vec2(missileSprite->getPositionX() - missileSprite->getContentSize().width,
		missileSprite->getPositionY()));
	
	fire->setEmitterMode(ParticleSystem::Mode::GRAVITY);
	fire->setTotalParticles(200);
	fire->setGravity(Vec2(200, 0));

	layer->addChild(fire);
}

Sequence * RangeMissile::missileAction()
{
	auto moveRight = MoveBy::create(RANGE_MISSILE_FLYING_DURATION, Vec2(visibleSize.width + missileSprite->getContentSize().width * 2, 0));
	auto removeMissile = CallFunc::create(missileSprite, callfunc_selector(Sprite::removeFromParent));
	auto missileSequence = Sequence::create(moveRight, removeMissile, NULL);

	return missileSequence;
}

Sequence * RangeMissile::particleAction()
{
	auto moveRight = MoveBy::create(RANGE_MISSILE_FLYING_DURATION, Vec2(visibleSize.width + missileSprite->getContentSize().width * 2, 0));
	auto removeParticle = CallFunc::create(fire, callfunc_selector(ParticleFire::removeFromParent));
	auto particleSequence = Sequence::create(moveRight, removeParticle, NULL);

	return particleSequence;
}
