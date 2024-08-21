#pragma once

#include "CollisionComponent.h"

class CircleCollisionComponent : public CollisionComponent
{
public:
	CLASS_DECLARATION(CircleCollisionComponent)
	CLASS_PROTOTYPE(CircleCollisionComponent)



	// Inherited via CollisionComponent
	void Initialize() override;

	void Update(float dt) override;

	bool CheckCollision(const CollisionComponent const* collision) override;

public:
	float radius{ 0 };
};