#pragma once
 
#include "Core/Serializable.h"
#include<string>

// the backslash allows us to make a macro that is longer than one line
//the # lets us turn the class name into a string
#define CLASS_DECLARATION(class) \
	static const char* GetTypeName() { return #class; }\
	virtual void Read(const json_t& value);\
	virtual void Write(json_t& value);

class Object : public Serializable
{
public:
	Object() = default; //this line IS optional, but it's good form
	Object(const std::string& name) : name{ name } {}
	virtual ~Object() = default;

	CLASS_DECLARATION(Object)

	virtual void Initialize() = 0;
	virtual void Activate() { active = true; }
	virtual void Deactivate() { active = false; }

public: //letting our variables be public because we don't want to have so many getters and setters (This IS bad form though)
	std::string name; 
	bool active{ false };
};