#pragma once

#include "Components/Component.h"
#include "Framework/Actor.h"

class EnemyComponent : public Component
{
public:
	CLASS_DECLARATION(EnemyComponent);
	CLASS_PROTOTYPE(EnemyComponent);

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);

	void Run();
	void Jump();

public:
	float speed{ 70 };
	float thrust = 1;
	int health{ 1 };

	float lastJump = 1.0f;
};

