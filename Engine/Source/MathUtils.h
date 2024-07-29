#pragma once
#include <cmath> 



namespace Math
{
	constexpr float Pi		= 3.14159265359f; //180 degrees
	constexpr float TwoPi	= 6.28318530718f; //360 degrees
	constexpr float HalfPi	= 1.57079632679f; //90 degrees
	//constexpr = "constant expresion" (converts at compile time rather than runtime if it has a constant as the input argument

	constexpr float RadToDeg(float radians) { return radians * (180.0f / Pi); }
	constexpr float DegToRad(float degrees) { return degrees * (Pi / 180.0f); }


	inline float Sin(float radians)
	{
		return std::sinf(radians);
	}

	inline float Cos(float radians)
	{
		return std::cosf(radians);
	}

	inline float Sqrt(float value)
	{
		return std::sqrtf(value);
	}

	//arc tangent (2 for two perameters)
	inline float Atan2(float y, float x)
	{
		return std::atan2f(y, x);
	}
	
	//returns which ever one is larger
	template<typename T> //template is a variable type iiuc. Allows you to put in different types ao that you don't need to overload functions
	T Max(T a, T b)
	{
		return (a > b) ? a : b; //if a is greater than b, return a else return b (is what that means)
	}

	template<typename T> //has to be put for each function you use it in iiuc
	T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template<typename T>
	T Abs(T value)
	{
		return (value < 0) ? -value : value;
		//value < 0 or value += (value * 2);
		
	}


	template<typename T>
	inline T Clamp(T v, T min, T max)
	{
		if (v < min) return min;
		if (v > max) return max;

		return v;

		//return (value < min) ? min : (value > max) ? : value;
	}


	inline int Wrap(int value, int max)
	{
		return value % max + ((value < 0) ? max : 0);
	}
	
	inline float Wrap(float value, float max)
	{
		return std::fmodf(value, max) + ((value < 0) ? max : 0);
	}

}