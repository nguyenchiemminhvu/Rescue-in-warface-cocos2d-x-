#ifndef __VECTOR_2D_H__
#define __VECTOR_2D_H__

#pragma once

class Vector2D
{
public:
	Vector2D();
	Vector2D(int x, int y);
	virtual ~Vector2D();

	void setX(int x);
	void setY(int y);

	int getX();
	int getY();

	float length();

	float dotProduct(const Vector2D& anotherVector);
	
	bool operator == (const Vector2D& anotherVector);
	Vector2D& operator = (const Vector2D& anotherVector);
	Vector2D& operator + (const Vector2D& anotherVector);
	Vector2D& operator - (const Vector2D& anotherVector);
	Vector2D& operator * (const int& value);
	Vector2D& operator / (const int& value);

private:
	int _x;
	int _y;
};

#endif //__VECTOR_2D_H__
