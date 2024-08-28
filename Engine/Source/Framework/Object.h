#pragma once
 
#include "Core/Serializable.h"
#include "Core/Factory.h"
#include<string>

// the backslash allows us to make a macro that is longer than one line
//the # lets us turn the class name into a string
#define CLASS_DECLARATION(classname)						\
	static const char* GetTypeName() { return #classname; }	\
	virtual void Read(const json_t& value);					\
	virtual void Write(json_t& value);

//## concatinates
#define FACTORY_REGISTER(classname)\
	class Register##classname\
	{\
	public:\
		Register##classname(){\
			Factory::Instance().Register<classname>(#classname);\
		}\
	};\
	static Register##classname register_instance;
// slashes at the end of each of those lines because it's a multi-line macro

#define CLASS_PROTOTYPE(classname) \
	virtual std::unique_ptr<Object> Clone()\
	 { \
		return std::make_unique<classname>(*this);\
	}

class Object : public Serializable
{
public:
	Object() = default; //this line IS optional, but it's good form
	Object(const std::string& name) : name{ name } {}
	virtual ~Object() = default;

	virtual std::unique_ptr<Object> Clone() = 0;

	CLASS_DECLARATION(Object)

	virtual void Initialize() = 0;
	virtual void Activate() { active = true; }
	virtual void Deactivate() { active = false; }

public: //letting our variables be public because we don't want to have so many getters and setters (This IS bad form though)
	std::string name; 
	bool active{ true };
	bool persistent{ false };
};