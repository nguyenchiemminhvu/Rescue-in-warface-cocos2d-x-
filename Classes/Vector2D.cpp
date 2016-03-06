/*
- Project: Rescue in warface
- Author: Nguyen Chiem Minh Vu

- First release: 00:20 07/03/2016
*/

#include "Vector2D.h"
#include <cmath>


Vector2D::Vector2D()
{
	_x = _y = 0;
}

Vector2D::Vector2D(int x, int y)
{
	_x = x;
	_y = y;
}

Vector2D::~Vector2D()
{
}

void Vector2D::setX(int x)
{
	this->_x = x;
}

void Vector2D::setY(int y)
{
	this->_y = y;
}

int Vector2D::getX()
{
	return this->_x;
}

int Vector2D::getY()
{
	return this->_y;
}

float Vector2D::length()
{
	return sqrt(_x * _x + _y * _y);
}

float Vector2D::dotProduct(const Vector2D & anotherVector)
{
	return (this->_x * anotherVector._x + this->_y * anotherVector._y);
}

bool Vector2D::operator==(const Vector2D & anotherVector)
{
	return (this->_x == anotherVector._x && this->_y == anotherVector._y);
}

Vector2D & Vector2D::operator=(const Vector2D & anotherVector)
{
	if (this == &anotherVector) {
		return *this;
	}

	this->_x = anotherVector._x;
	this->_y = anotherVector._y;

	return *this;
}

Vector2D & Vector2D::operator+(const Vector2D & anotherVector)
{
	this->_x += anotherVector._x;
	this->_y += anotherVector._y;

	return *this;
}

Vector2D & Vector2D::operator-(const Vector2D & anotherVector)
{
	this->_x -= anotherVector._x;
	this->_y -= anotherVector._y;

	return *this;
}

Vector2D & Vector2D::operator*(const int & value)
{
	this->_x *= value;
	this->_x *= value;

	return *this;
}

Vector2D & Vector2D::operator/(const int & value)
{
	if (value != 0) {
		this->_x /= value;
		this->_y /= value;

		return *this;
	}

	return *this;
}