#pragma once
#include <string>
#include<variant>


//kinda like typename. This is an alias.
//Either could be used but I'm going to use an alias
using id_t = std::string;

struct Event
{
	using data_t = std::variant<int, bool, float, std::string > ;

	Event(const id_t& id, data_t data) : id{ id }, data{ data } {}

	id_t id;
	data_t data;
	
};