#pragma once
#include<string>
#include<algorithm>

//can't return references on these two strings because the function goes out of scope and the variables are temporary
std::string ToLower(const std::string& str);
std::string ToUpper(const std::string& str);

bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2);