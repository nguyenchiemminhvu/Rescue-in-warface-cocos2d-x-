/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#include "Player.h"
#include "PhysicsBodyParser\PhysicsBodyParser.h"


Player::Player(Layer * layer)
{
	this->layer = layer;
	loadPlayerSprite(layer);
	loadPlayerGun(layer);
	initPlayerPhysicsBody();
	keys = new bool[1024];
	for (int i = 0; i < 1024; i++)
		keys[i] = false;
}


Player::~Player()
{
	this->removeFromParentAndCleanup(true);
	delete[] keys;
}


Vec2 Player::getPlayerGunPosition()
{
	return playerGun->getPosition();
}


void Player::handleKeyPressedEvent(cocos2d::EventKeyboard::KeyCode keyCode)
{
	keys[(int)keyCode] = true;
}


void Player::handleKeyReleasedEvent(cocos2d::EventKeyboard::KeyCode keyCode)
{
	keys[(int)keyCode] = false;
}


void Player::move(float dt)
{
	if (keys[(int)EventKeyboard::KeyCode::KEY_W]) {
		playerSprite->setPositionY(playerSprite->getPositionY() + FLYING_SPEED * dt);
		if (playerSprite->getPositionY() > origin.y + visibleSize.height - playerSprite->getContentSize().height * 1.5)
			getBack();
	}

	if (keys[(int)EventKeyboard::KeyCode::KEY_S]) {
		playerSprite->setPositionY(playerSprite->getPositionY() - FLYING_SPEED * dt);
	}

	if (keys[(int)EventKeyboard::KeyCode::KEY_A]) {
		playerSprite->setPositionX(playerSprite->getPositionX() - FLYING_SPEED * dt);
		if (playerSprite->getPositionX() < origin.x + playerSprite->getContentSize().width)
			getBack();
	}

	if (keys[(int)EventKeyboard::KeyCode::KEY_D]) {
		playerSprite->setPositionX(playerSprite->getPositionX() + FLYING_SPEED * dt);
		if (playerSprite->getPositionX() > origin.x + visibleSize.width - playerSprite->getContentSize().width)
			getBack();
	}
}

void Player::getBack()
{
	playerSprite->setPosition(previousPosition);
}

void Player::lostControl()
{
	auto rotation = RotateBy::create(2, 45.0f);
	auto moveDown = MoveBy::create(HELICOPTER_LOST_CONTROLL_DURATION, Vec2(0, -visibleSize.height));
	playerSprite->runAction(Spawn::create(rotation, moveDown, NULL));
}

void Player::update(float dt)
{
	previousPosition = playerSprite->getPosition();
	move(dt);
	shiftPlayerGun();
}

void Player::loadPlayerSprite(Layer *layer)
{
	origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	
	playerSprite = Sprite::create("helicopter_transportation.png");
	playerSprite->setPosition(Vec2(origin.x + playerSprite->getContentSize().width * 2,
								   origin.y + GROUND_THICKNESS + playerSprite->getContentSize().height));
	previousPosition = Vec2(origin.x + playerSprite->getContentSize().width * 2,
							origin.y + GROUND_THICKNESS + playerSprite->getContentSize().height);
	layer->addChild(playerSprite);
}

void Player::loadPlayerGun(Layer * layer)
{
	playerGun = Sprite::create("minigun.png");
	playerGun->setPosition(Vec2((playerSprite->getContentSize().width + playerGun->getContentSize().width) / 2, 
								 (playerSprite->getContentSize().height - playerGun->getContentSize().height) / 2));
	layer->addChild(playerGun, 1);
	shiftPlayerGun();
}


void Player::shiftPlayerGun()
{
	playerGun->setPosition(Vec2(playerSprite->getPositionX() + playerGun->getContentSize().width / 2,
								playerSprite->getPositionY() - playerGun->getContentSize().height / 2));
}


void Player::initPlayerPhysicsBody()
{
	auto playerBody = PhysicsBodyParser::getInstance()->bodyFormJson(playerSprite, "player", PhysicsMaterial(999, 0, 0));
	playerBody->setContactTestBitmask(true);
	playerBody->setCollisionBitmask(PLAYER_COLLISTION_BITMASK);

	playerSprite->setPhysicsBody(playerBody);
}
