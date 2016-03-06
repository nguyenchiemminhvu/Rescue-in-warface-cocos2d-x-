#include "RangeMissile.h"
#include "Defination.h"
#include "PhysicsBodyParser\PhysicsBodyParser.h"
#include "SimpleAudioEngine.h"


RangeMissile * RangeMissile::spawnRangeMissile(cocos2d::Layer *layer, float playerPositionY)
{
	return new RangeMissile(layer, playerPositionY);
}

RangeMissile::RangeMissile(cocos2d::Layer *layer, float playerPositionY)
{
	this->layer = layer;

	origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	this->createMissileSprite(playerPositionY);
	this->createParticleFire();
	this->createMissileBody();

	missileSprite->runAction(missileAction());
	fire->runAction(particleAction());
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/missile_sound.mp3");
}


RangeMissile::~RangeMissile()
{
	CC_SAFE_DELETE(missileSprite);
}

void RangeMissile::createMissileSprite(float playerPositionY)
{
	missileSprite = Sprite::create("missile.png");

	missileSprite->setAnchorPoint(Vec2(1, 0.5));

	float positionY = random(playerPositionY - 100, playerPositionY + 100);
	if (positionY < origin.y + GROUND_THICKNESS + 100) {
		positionY = random(playerPositionY, playerPositionY + 200);
	}
	missileSprite->setPosition(Vec2(origin.x, positionY));

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

void RangeMissile::createMissileBody()
{
	PhysicsBodyParser::getInstance()->parseJsonFile("CustomPhysicsBody.json");

	auto missileBody = PhysicsBodyParser::getInstance()->bodyFormJson(missileSprite, "range_missile", PhysicsMaterial(1, 1, 0));
	missileBody->setDynamic(false);
	missileBody->setContactTestBitmask(true);
	missileBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);

	missileSprite->setPhysicsBody(missileBody);
}

Sequence * RangeMissile::missileAction()
{
	auto moveRight = MoveBy::create(RANGE_MISSILE_FLYING_DURATION, Vec2(visibleSize.width + missileSprite->getContentSize().width * 2, 0));
	auto removeMissile = CallFunc::create(missileSprite, callfunc_selector(Sprite::removeFromParent));
	auto removeAll = CallFunc::create(this, callfunc_selector(RangeMissile::removeAll));
	auto missileSequence = Sequence::create(moveRight, removeMissile, removeAll, NULL);

	return missileSequence;
}

Sequence * RangeMissile::particleAction()
{
	auto moveRight = MoveBy::create(RANGE_MISSILE_FLYING_DURATION, Vec2(visibleSize.width + missileSprite->getContentSize().width * 2, 0));
	auto removeParticle = CallFunc::create(fire, callfunc_selector(ParticleFire::removeFromParent));
	auto particleSequence = Sequence::create(moveRight, NULL);

	return particleSequence;
}

void RangeMissile::removeAll()
{
	fire->removeFromParentAndCleanup(true);
	this->removeFromParentAndCleanup(true);
}
