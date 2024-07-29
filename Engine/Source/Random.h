#pragma once

#include "Vector2.h"
#include "MathUtils.h"
#include<random>


inline int random() { return rand(); }
inline int random(unsigned int max) { return rand() % max; }
inline int random(int min, int max) { return min + rand() % (max - min); }

inline float randomf() { return rand() / (float)RAND_MAX; } //0 -1
inline float randomf(float max) { return max * randomf(); } //0 and max number
inline float randomf(float min, float max) { return min + randomf(max - min); }

inline Vector2 randomOnUnitCircle() //ON circle is on perameter of circle (random in unit circle would be anywhere within a unit circle)
{
	float angle = randomf(0, 360);
	return Vector2{ Math::Cos(Math::DegToRad(angle)), Math::Sin(Math::DegToRad(angle)) };
}

