#pragma once

#include "Math.h"
#include <iostream>
#include <cfloat>

class Vector3D
{
	friend std::ostream& operator<<(std::ostream& output, const Vector3D& vector);

public:
	explicit Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f);
	explicit Vector3D(int x, int y, int z);
	Vector3D(const Vector3D& rhs);
	~Vector3D();


	//Math operators
	Vector3D& operator+= (const Vector3D& rhs);
	Vector3D& operator-= (const Vector3D& rhs);
	Vector3D& operator*= (float mult);
	Vector3D& operator/= (float div);
	Vector3D& operator= (const Vector3D& rhs);

	bool operator== (const Vector3D& rhs) const;
	bool operator!= (const Vector3D& rhs) const;

	Vector3D operator+(const Vector3D& other) const;
	Vector3D operator-(const Vector3D& other) const;
	Vector3D operator*(float mult) const;
	Vector3D operator/(float div) const;

	//Getters and Setters
	inline float getX() const { return mX; }
	inline float getY() const { return mY; }
	inline float getZ() const { return mZ; }

	inline void setX(float x) { mX = x; }
	inline void setY(float y) { mY = y; }
	inline void setZ(float z) { mZ = z; }

	//Helper Functions
	bool hasNonZeroLength() const;
	float getLength() const;
	float getLengthSquared() const; //more efficient than get length - use when comparing distances and actual distance is not needed

	void normalize();
	Vector3D getNormalizedVector() const; // returns a vector of length 1 but leaves the original vector unchanged
	float dotProduct(const Vector3D& other) const;
	float dotProduct(const Vector3D& other, float theta) const;
	Vector3D crossProduct(const Vector3D& other) const;

private:
	float mX;
	float mY;
	float mZ;
};

//std::ostream& operator<< (std::ostream& out, const Vector3D& vector);
//const Vector3D ZERO_VECTOR3D(0.0f, 0.0f, 0.0f); //useful when we need to return a pointer to a default vector from a function

