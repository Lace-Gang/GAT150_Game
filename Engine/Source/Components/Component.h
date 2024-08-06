#pragma once

#include "../Framework/Object.h"


class Component :public Object
{
public:
	virtual void Update(float dt) =0;  //"=0" forces child classes to do this, "{}" gives the choice to use it
public:
	class Actor* owner{ nullptr };
};