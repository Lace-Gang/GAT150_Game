#pragma once
#include <string>

//(void)0 is a no opperation by the way (basically telling to do nothing)
//ASSERT will be expression
//if expression true, do nothing, else do suctom assert
//will only run in debug mode, else do nothing
#ifdef _DEBUG
	#define ASSERT(expr)  ((expr) ? (void)0 : CustomAssert(#expr, __FILE__, __LINE__))
#else
	#define ASSERT(expr) (void)0
#endif


void CustomAssert(const std::string& expression, const std::string& filename, int line);