#pragma once

#include "Math.h"
#include "Vector3D.h"
#include <iostream>
#include <cfloat>

class Vector2D
{
	friend std::ostream& operator<<(std::ostream& output, const Vector2D& vector);

public:
	explicit Vector2D(float x = 0.0f, float y = 0.0f);
	explicit Vector2D(int x, int y);
	Vector2D(const Vector2D& rhs);
	~Vector2D();

	//Math operators
	Vector2D& operator+= (const Vector2D& rhs);
	Vector2D& operator-= (const Vector2D& rhs);
	Vector2D& operator*= (float mult);
	Vector2D& operator/= (float div);
	Vector2D& operator= (const Vector2D& rhs);

	bool operator== (const Vector2D& rhs)const;
	bool operator!= (const Vector2D& rhs)const;

	Vector2D operator+(const Vector2D& other) const;
	Vector2D operator-(const Vector2D& other) const;
	Vector2D operator*(float mult) const;
	Vector2D operator/(float div) const;

	//Getters and Setters
	inline float getX() const { return mX; };
	inline float getY() const { return mY; };
	inline void setX(float x) { mX = x; };
	inline void setY(float y) { mY = y; };

	//Helper Functions
	Vector3D get3DVector();
	bool hasNonZeroLength() const;
	float getLength() const;
	float getLengthSquared() const; //more efficient than get length - use when comparing distances and actual distance is not needed

	void normalize();
	Vector2D getNormalizedVector() const; // returns a vector of length 1 but leaves the original vector unchanged
	float dotProduct(const Vector2D& other) const;
	float dotProduct(const Vector2D& other, float theta) const;

private:
	float mX;
	float mY;
};

