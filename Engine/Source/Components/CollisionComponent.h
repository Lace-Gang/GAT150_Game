#pragma once

#include "Component.h"


class CollisionComponent : public Component
{
public:
	//one const is cannot change the address, one is cannot change the thing being pointed to
	virtual bool CheckCollision (const CollisionComponent const * collision) = 0;
};