#include "Player.h"


Player::Player(Layer * layer)
{
	
}

Player::~Player()
{
}

int Player::getPosX()
{
	return playerPos.getX();
}

int Player::getPosY()
{
	return playerPos.getY();
}

void Player::setPosX(int x)
{
	playerPos.setX(x);
}

void Player::setPosY(int y)
{
	playerPos.setY(y);
}

void Player::handleKeyDownEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		break;

	case EventKeyboard::KeyCode::KEY_S:
		break;

	case EventKeyboard::KeyCode::KEY_A:
		break;

	case EventKeyboard::KeyCode::KEY_D:
		break;
	}
}

void Player::handleKeyReleaseEvent(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		break;

	case EventKeyboard::KeyCode::KEY_S:
		break;

	case EventKeyboard::KeyCode::KEY_A:
		break;

	case EventKeyboard::KeyCode::KEY_D:
		break;
	}
}

void Player::update(float dt)
{

}
