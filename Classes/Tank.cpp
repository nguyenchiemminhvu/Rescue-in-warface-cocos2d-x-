#include "Tank.h"
#include "Defination.h"

void Tank::spawnTank(Layer * layer)
{
	Tank *tank = new Tank(layer);
}

Tank::Tank(Layer * layer)
{
	this->layer = layer;
	visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	tankSprite = Sprite::create("tank_air_defense.png");
	tankSprite->setPosition(origin.x + visibleSize.width + cocos2d::random(-100, 100),
							origin.y + GROUND_THICKNESS - tankSprite->getContentSize().height / 2);

	this->layer->addChild(tankSprite);

	auto moveLeft1 = MoveBy::create(TANK_RELOAD_DURATION, Vec2(-100, 0));
	auto launch = CallFunc::create(this, callfunc_selector(Tank::launchMissile));
	auto step1 = Sequence::create(moveLeft1, launch, NULL);

	auto moveLeft2 = MoveBy::create(TANK_RELOAD_DURATION * 2, Vec2(-200, 0));
	auto step2 = Sequence::create(moveLeft2, launch, NULL);

	auto moveLeft3 = MoveBy::create(TANK_RELOAD_DURATION * 3, Vec2(-700, 0));
	auto step3 = Sequence::create(moveLeft3, NULL);

	auto tankSequence = Sequence::create(step1, step2, step3, CallFunc::create(tankSprite, callfunc_selector(Sprite::removeFromParent)), NULL);

	tankSprite->runAction(tankSequence);
}

Tank::~Tank()
{
	CC_SAFE_DELETE(tankSprite);
}

Vec2 Tank::tankPosition()
{
	return tankSprite->getPosition();
}

void Tank::launchMissile()
{
	tankMissile = cocos2d::Sprite::create("tank_ammo.png");
	tankMissile->setPosition(tankPosition());
	this->layer->addChild(tankMissile, 1000);

	//tank's missile sequence action
	auto missileFlying = MoveTo::create(1, Vec2(cocos2d::random(origin.x + 100, origin.x + 400), cocos2d::random(origin.y + GROUND_THICKNESS + 100, origin.y + visibleSize.height - 100)));
	auto explode = CallFunc::create(this, callfunc_selector(Tank::missileExplode));
	
	tankMissile->runAction(Sequence::create(missileFlying, explode, NULL));
}

void Tank::missileExplode()
{
	cocos2d::log("(%d, %d)\n", tankMissile->getPositionX(), tankMissile->getPositionY()); //can't get the position of missile after launched
	tankMissile->removeFromParent();
}
