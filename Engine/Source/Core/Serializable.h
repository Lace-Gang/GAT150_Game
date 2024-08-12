#pragma once

#include "Json.h"

//serializable exposes data to another format
class Serializable
{
public:
	//virtual makes sure the destructor is called for all children and not just this one class
	virtual ~Serializable() = default;

	virtual void Read(const json_t& value) = 0;
	virtual void Write(json_t& value) = 0;
};

//public, protected, private is the typical order in a class 
// (but obviously any workplace would be different)
//When in Rome . . .