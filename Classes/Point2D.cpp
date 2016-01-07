#include "Point2D.h"
#include <cmath>


Point2D::Point2D()
{
	_x = _y = 0;
}

Point2D::Point2D(int x, int y)
{
	_x = x;
	_y = y;
}


Point2D::~Point2D()
{
}

void Point2D::setX(int x)
{
	this->_x = x;
}

void Point2D::setY(int y)
{
	this->_y = y;
}

int Point2D::getX()
{
	return this->_x;
}

int Point2D::getY()
{
	return this->_y;
}

Point2D& Point2D::operator=(const Point2D & anotherPoint)
{
	if (this == &anotherPoint) {
		return *this;
	}

	this->_x = anotherPoint._x;
	this->_y = anotherPoint._y;

	return *this;
}

bool Point2D::operator==(const Point2D & anotherPoint)
{
	return (this->_x == anotherPoint._x && this->_y == anotherPoint._y);
}

void Point2D::translate(int vectorX, int vectorY)
{
	this->_x += vectorX;
	this->_y += vectorY;
}

float Point2D::distance(const Point2D & anotherPoint)
{
	int lengthX = anotherPoint._x - this->_x;
	int lengthY = anotherPoint._y - this->_y;

	return sqrt(lengthX * lengthX + lengthY * lengthY);
}
