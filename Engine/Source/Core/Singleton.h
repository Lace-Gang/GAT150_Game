#pragma once

template <typename T>
class Singleton
{
public:
	Singleton(const Singleton& other) = delete; //disallows copy constructors
	Singleton& operator = (const Singleton& other) = delete; //disallows assignment opperators

	static T& Instance()
	{
		static T instance; //variable will not go out of scope (I think?)
		return instance;
	}

protected:
	Singleton() = default;
};

//singletons prevent the following things:

//copy constructor
//Student s1;
//Student s2(s1);

//assignment opperator
//s2 = s1;
