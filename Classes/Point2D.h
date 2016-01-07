#ifndef __POINT_2D_H__
#define __POINT_2D_H__

#pragma once

class Point2D
{
public:
	Point2D();
	Point2D(int x, int y);
	virtual ~Point2D();

	void setX(int x);
	void setY(int y);

	int getX();
	int getY();

	Point2D& operator= (const Point2D& anotherPoint);
	bool operator== (const Point2D& anotherPoint);

	void translate(int vectorX, int vectorY);

	float distance(const Point2D& anotherPoint);

private:
	int _x;
	int _y;
};

#endif //__POINT_2D_H__