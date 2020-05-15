#pragma once

#include "Math.h"
#include "Vector3D.h"
#include <iostream>
#include <cfloat>

class Vector2D 
{
	friend std::ostream& operator<<(std::ostream& output, const Vector2D& vector);

public:
	Vector2D(float x = 0.0f, float y = 0.0f);
	~Vector2D();

private:

};

