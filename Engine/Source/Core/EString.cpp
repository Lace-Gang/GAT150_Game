#include "EString.h"

//not only does the const prevent us from messing with the varialbe
//but it ALSO allows us to pass in a literal if we want.
//can't do it otherwise
std::string ToLower(const std::string& str)
{
	std::string lower;
	lower.resize(str.size());

	
	//here's the modern c++ way to do it
	//this is called an algorithem (algorythem?)
	std::transform(str.begin(), str.end(), lower.begin(),
		[](char c)
		{
			return std::tolower(c);
		});
	//uses a "predicate" (the function in the argument), it's also called a lamda (or an anonymous function because it has no name)

	return lower;
}

std::string ToUpper(const std::string& str)
{
	std::string upper;
	upper.resize(str.size());
	
	std::transform(str.begin(), str.end(), upper.begin(),
		[](char c)
		{
			return std::toupper(c);
		});

	return upper;
}

bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2)
{
	if (str1.length() != str2.length()) return false;
	
	//we can return an algorithem directly
	return std::equal(str1.begin(), str1.end(), str2.begin(),
		[](char c1, char c2)
		{
			return std::tolower(c1) == tolower(c2);
		});
	//also, there's no particular reason why we can't just to lower both strings and then compair them. But . . . . for funsies I guess?

}
