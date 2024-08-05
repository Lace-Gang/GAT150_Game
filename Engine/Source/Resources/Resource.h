#pragma once
#include <string>
#include <memory>
#include<cstdarg>

class Resource
{
public:
	Resource() = default;
	~Resource() = default;

	//variadic requirements  (requirements may vary)
	virtual bool Create(std::string name, ...) = 0;
};

template<typename T = Resource> //enforcing that the type must at least be a resource type
using res_t = std::shared_ptr<T>;

