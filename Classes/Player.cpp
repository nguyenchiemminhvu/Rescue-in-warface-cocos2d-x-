#include "Player.h"


Player::Player(Layer * layer)
{
	loadPlayerSprite(layer);
	limitedPlayerArea();
	initPlayerPhysicsBody();
}

Player::~Player()
{
	CC_SAFE_DELETE(playerSprite);
}

void Player::handleKeyPressedEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
}

void Player::handleKeyReleaseEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
}

void Player::handleMouseMoveEvent(cocos2d::EventMouse * event)
{
	mousePosition.setX(origin.x + event->getCursorX());
	mousePosition.setY(origin.y + event->getCursorY());
}

float Player::approachMousePosition(float separation, float dt)
{
	float different = separation * dt;
	
	return different;
}

void Player::update(float dt)
{
	//save temporarily player position
	playerPrePosition = playerSprite->getPosition();

	float differentX = mousePosition.getX() - playerSprite->getPositionX();
	float differentY = mousePosition.getY() - playerSprite->getPositionY();

	playerCurrentVelocity.setX(approachMousePosition(differentX, dt));
	playerCurrentVelocity.setY(approachMousePosition(differentY, dt));

	playerSprite->setPositionX(playerSprite->getPositionX() + playerCurrentVelocity.getX());
	playerSprite->setPositionY(playerSprite->getPositionY() + playerCurrentVelocity.getY());

	//check player position get out of range
	if (!activitiesArea.containsPoint(playerSprite->getPosition())) {
		//get back
		playerSprite->setPosition(playerPrePosition);
	}
}


void Player::loadPlayerSprite(Layer *layer)
{
	origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	playerSprite = Sprite::create("helicopter_transportation.png");
	playerSprite->setPosition(Vec2(origin.x + playerSprite->getContentSize().width * 2,
		origin.y + GROUND_THICKNESS + playerSprite->getContentSize().height));
	playerPrePosition = playerSprite->getPosition();
	layer->addChild(playerSprite);
}

void Player::limitedPlayerArea()
{
	activitiesArea.setRect(0, GROUND_THICKNESS, visibleSize.width, visibleSize.height);
}

void Player::initPlayerVelocity()
{
	playerCurrentVelocity.setX(0);
	playerCurrentVelocity.setY(0);

	mousePosition.setX(playerSprite->getPositionX());
	mousePosition.setY(playerSprite->getPositionY());
}

void Player::initPlayerPhysicsBody()
{
	auto playerBody = PhysicsBody::createBox(Size(playerSprite->getContentSize().width, playerSprite->getContentSize().height / 2));
	playerBody->setContactTestBitmask(true);
	playerBody->setCollisionBitmask(PLAYER_COLLISTION_BITMASK);

	playerSprite->setPhysicsBody(playerBody);
}
