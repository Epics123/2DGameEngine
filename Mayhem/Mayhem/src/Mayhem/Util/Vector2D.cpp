#include "mpch.h"
#include "Vector2D.h"

Vector2D::Vector2D(float x, float y)
:mX(x)
,mY(y)
{
}

Vector2D::Vector2D(int x, int y)
:mX((float)x)
,mY((float)y)
{
}

Vector2D::Vector2D(const Vector2D& rhs)
:mX(rhs.mX)
,mY(rhs.mY)
{
}

Vector2D::~Vector2D()
{
}

Vector2D& Vector2D::operator+=(const Vector2D& rhs)
{
	mX += rhs.mX;
	mY += rhs.mY;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& rhs)
{
	mX -= rhs.mX;
	mY -= rhs.mY;
	return *this;
}

Vector2D& Vector2D::operator*=(float mult)
{
	mX *= mult;
	mY *= mult;
	return *this;
}

Vector2D& Vector2D::operator/=(float div)
{
	mX /= div;
	mY /= div;
	return *this;
}

Vector2D& Vector2D::operator=(const Vector2D& rhs)
{
	mX = rhs.mX;
	mY = rhs.mY;
	return *this;
}

bool Vector2D::operator==(const Vector2D& rhs) const
{
	if ((getX() == rhs.getX()) && (getY() == rhs.getY()))
		return true;
	else 
		return false;
}

bool Vector2D::operator!=(const Vector2D& rhs) const
{
	if ((getX() == rhs.getX()) && (getY() == rhs.getY()))
		return false;
	else 
		return true;
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
	Vector2D result = *this;
	result += other;
	return result;
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
	Vector2D result = *this;
	result -= other;
	return result;
}

Vector2D Vector2D::operator*(float mult) const
{
	Vector2D result = *this;
	result.mX *= mult;
	result.mY *= mult;

	return result;
}

Vector2D Vector2D::operator/(float div) const
{
	Vector2D result = *this;
	result.mX /= div;
	result.mY /= div;

	return result;
}

Vector3D Vector2D::get3DVector()
{
	return Vector3D(mX, mY, 0.0f);
}

bool Vector2D::hasNonZeroLength() const
{
	if (mX != 0.0f || mY != 0.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Vector2D::getLength() const
{
	float lengthSquared = getLengthSquared();
	return sqrt(lengthSquared);
}

float Vector2D::getLengthSquared() const
{
	float lengthSquared = (mX * mX) + (mY * mY);
	return lengthSquared;
}

void Vector2D::normalize()
{
	float invLength = 1.0f / (getLength() + FLT_MIN);
	mX *= invLength;
	mY *= invLength;
}

Vector2D Vector2D::getNormalizedVector() const
{
	Vector2D newVector(*this);
	newVector.normalize();
	return newVector;
}

float Vector2D::dotProduct(const Vector2D& other) const
{
	return mX * other.mX + mY * other.mY;
}

float Vector2D::dotProduct(const Vector2D& other, float theta) const
{
	return getLength() * other.getLength() * cos(theta);
}

std::ostream& operator<<(std::ostream& output, const Vector2D& vector)
{
	output << "(" << vector.getX() << ", " << vector.getY() << ")";
	return output;
}