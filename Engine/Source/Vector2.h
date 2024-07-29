#pragma once
#include "MathUtils.h"
#include <cmath> 


//Struct means default access level is public
struct Vector2
{
	float x;
	float y;
	
	Vector2() = default;
	Vector2(float x, float y) { this->x = x; this->y = y; }
	Vector2(int x, int y) { this->x = (float)x; this->y = (float)y; }

	Vector2 Add(Vector2 v) { return Vector2{x + v.x, y +v.y}; }



	//the index I think sort of adds onto the address of x since x and y are next to each other in memory
	float operator [] (unsigned int index) const { return (& x)[index]; }
	float& operator [] (unsigned int index) { return (&x)[index]; }
	

	Vector2 operator + ( const Vector2& v) const { return Vector2{ x + v.x, y + v.y }; }
	Vector2 operator - (const Vector2& v) const { return Vector2{ x - v.x, y - v.y }; }
	Vector2 operator * (const Vector2& v) const { return Vector2{ x * v.x, y * v.y }; }
	Vector2 operator / (const Vector2& v) const { return Vector2{ x / v.x, y / v.y }; }

	Vector2 operator + (float s) const { return Vector2{ x + s, y + s }; }
	Vector2 operator - (float s) const { return Vector2{ x - s, y - s }; }
	Vector2 operator * (float s) const { return Vector2{ x * s, y * s }; }
	Vector2 operator / (float s) const { return Vector2{ x / s, y / s }; }

	Vector2& operator += (const Vector2& v) { x += v.x; y += v.y; return *this; }
	Vector2& operator -= (const Vector2& v) { x -= v.x; y -= v.y; return *this; }
	Vector2& operator *= (const Vector2& v) { x *= v.x; y *= v.y; return *this; }
	Vector2& operator /= (const Vector2& v) { x /= v.x; y /= v.y; return *this; }
	
	Vector2& operator += (float s) { x += s; y += s; return *this; }
	Vector2& operator -= (float s) { x -= s; y -= s; return *this; }
	Vector2& operator *= (float s) { x *= s; y *= s; return *this; }
	Vector2& operator /= (float s) { x /= s; y /= s; return *this; }

	float LengthSqr() const { return (x * x) + (y * y); }
	float Length() const { return std::sqrt((x * x) + (y * y)); }

	float Angle() const { return Math::Atan2(y, x); }
	Vector2 Rotate(float radians) const;


	//vector magnitude (length) is gotton via pythagrian theorem (there is a function for this)
// v/||v|| is a normalized direction/vector/speed (so that direction does not increase speed too much)
	Vector2 Normalized() const { return *this / Length(); }
};




inline Vector2 Vector2::Rotate(float radians) const
{
	float x_ = x * Math::Cos(radians) - y * Math::Sin(radians);
	float y_ = x * Math::Sin(radians) + y * Math::Cos(radians);

	return { x_, y_ };
}