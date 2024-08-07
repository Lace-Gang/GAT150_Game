#pragma once

#include<rapidjson/document.h>
#include<string>


//macros
//macros are all uppercase (macrocase)
#define READ_DATA(value, data) Json::Read(value, #data, data)
// #data just puts strings around it


namespace Json
{
	bool Load(const std::string& filename, rapidjson::Document& document);
	bool Read(const rapidjson::Value& value, const std::string& name, int& data); //declarations don't technically NEED names, but it's good form
	bool Read(const rapidjson::Value& value, const std::string& name, bool& data);
	bool Read(const rapidjson::Value& value, const std::string& name, std::string &data);
	//maybe try to add a Read typename in later?

}