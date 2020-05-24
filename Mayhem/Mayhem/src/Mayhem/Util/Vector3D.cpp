#include "mpch.h"
#include "Vector3D.h"

Vector3D::Vector3D(float x, float y, float z)
:mX(x)
,mY(y)
,mZ(z)
{
}

Vector3D::Vector3D(const Vector3D& rhs)
:mX(rhs.mX)
,mY(rhs.mY)
,mZ(rhs.mZ)
{
}

Vector3D::Vector3D(int x, int y, int z)
:mX((float)x)
,mY((float)y)
,mZ((float)z)
{
}

Vector3D::~Vector3D()
{
}

Vector3D& Vector3D::operator+=(const Vector3D& rhs)
{
	mX += rhs.mX;
	mY += rhs.mY;
	mZ += rhs.mZ;

	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& rhs)
{
	mX -= rhs.mX;
	mY -= rhs.mY;
	mZ -= rhs.mZ;

	return *this;
}

Vector3D& Vector3D::operator*=(float mult)
{
	mX *= mult;
	mY *= mult;
	mZ *= mult;

	return *this;
}

Vector3D& Vector3D::operator/=(float div)
{
	mX /= div;
	mY /= div;
	mZ /= div;

	return *this;
}

Vector3D& Vector3D::operator=(const Vector3D& rhs)
{
	mX = rhs.mX;
	mY = rhs.mY;
	mZ = rhs.mZ;

	return* this;
}

bool Vector3D::operator==(const Vector3D& rhs) const
{
	if ((getX() == rhs.getX()) && (getY() == rhs.getY()) && (getZ() == rhs.getZ()))
		return true;
	else
		return false;
}

bool Vector3D::operator!=(const Vector3D& rhs) const
{
	if ((getX() == rhs.getX()) && (getY() == rhs.getY()) && (getZ() == rhs.getZ()))
		return false;
	else
		return true;
}

Vector3D Vector3D::operator+(const Vector3D& other) const
{
	Vector3D result = *this;
	result += other;
	return result;
}

Vector3D Vector3D::operator-(const Vector3D& other) const
{
	Vector3D result = *this;
	result -= other;
	return result;
}

Vector3D Vector3D::operator*(float mult) const
{
	Vector3D result = *this;
	result *= mult;
	return result;
}

Vector3D Vector3D::operator/(float div) const
{
	Vector3D result = *this;
	result /= div;
	return result;
}

bool Vector3D::hasNonZeroLength() const
{
	if (mX != 0.0f || mY != 0.0f || mZ != 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Vector3D::getLength() const
{
	float sqrLen = getLengthSquared();
	return sqrt(sqrLen);
}

float Vector3D::getLengthSquared() const
{
	float sqrLen = (mX * mX) + (mY * mY) + (mZ * mZ);
	return sqrLen;
}

void Vector3D::normalize()
{
	float inverseLength = 1.0f / (getLength() + FLT_MIN);
	mX *= inverseLength;
	mY *= inverseLength;
}

Vector3D Vector3D::getNormalizedVector() const
{
	Vector3D newVector(*this);
	newVector.normalize();
	return newVector;
}

float Vector3D::dotProduct(const Vector3D& other) const
{
	return (mX * other.mX) + (mY * other.mY) + (mZ * other.mZ);
}

float Vector3D::dotProduct(const Vector3D& other, float theta) const
{
	return getLength() * other.getLength() * cos(theta);
}

Vector3D Vector3D::crossProduct(const Vector3D& other) const
{
	Vector3D crsProduct;

	float x = (mY * other.getZ()) - (mZ * other.getY());
	float y = (mZ * other.getX()) - (mX * other.getZ());
	float z = (mX * other.getY()) - (mY * other.getX());

	crsProduct = Vector3D(x, y, z);
	return crsProduct;
}

std::ostream& operator<<(std::ostream& output, const Vector3D& vector)
{
	output << "(" << vector.getX() << ", " << vector.getY() << ", " << vector.getZ() << ")";
	return output;
}
