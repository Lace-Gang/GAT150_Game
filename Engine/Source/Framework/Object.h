#pragma once

#include<string>

class Object
{
public:
	Object() = default; //this line IS optional, but it's good form
	Object(const std::string& name) : name{ name } {}

	virtual void Initialize() = 0;
	virtual void Activate() { active = true; }
	virtual void Deactivate() { active = false; }

public: //letting our variables be public because we don't want to have so many getters and setters (This IS bad form though)
	std::string name; 
	bool active{ false };
};