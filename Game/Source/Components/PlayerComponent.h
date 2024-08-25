#pragma once

#include "Components/Component.h"

class PlayerComponent : public Component
{
public:
	CLASS_DECLARATION(PlayerComponent)
	CLASS_PROTOTYPE(PlayerComponent)

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);

	void Jump();

	//void Read(const json_t& value);
	//void Write(json_t& value);

public:
	float speed{ 0 };
	int health{ 1 };

	float lastJump = 1.0f;
};