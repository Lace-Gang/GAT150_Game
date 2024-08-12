#pragma once

#include "./Math/Vector2.h"
#include "./Renderer/Color.h"

#include<rapidjson/document.h>
#include<string>


//macros
//macros are all uppercase (macrocase)
#define READ_DATA(value, data) Json::Read(value, #data, data)
#define READ_DATA_REQUIRED(value, data) Json::Read(value, #data, data, true)
// #data just puts strings around the value inside data (basically a to string)


namespace Json
{
	bool Load(const std::string& filename, rapidjson::Document& document);
	bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool isRequired = false); //declarations don't technically NEED names, but it's good form
	bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, std::string &data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, Vector2& data, bool isRequired = false);
	bool Read(const rapidjson::Value& value, const std::string& name, class Color& data, bool isRequired = false);
	//maybe try to add a Read typename in later?

}

//gonna make sure we're not typing that out all the time
//using the the more prefered way (macros are just far too destructive)
using json_t = rapidjson::Value;

//typedef used to be the way to do it
//typedef rapidjson::Value json_t;