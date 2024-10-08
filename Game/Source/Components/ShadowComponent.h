#pragma once

#include "Components/Component.h"

class ShadowComponent : public Component
{
public:
	CLASS_DECLARATION(ShadowComponent);
	CLASS_PROTOTYPE(ShadowComponent)

	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);

	void Jump(float* speed);
	void JumpDown();

	//void Read(const json_t& value);
	//void Write(json_t& value);

public:
	float speed{ 0 };
	float storedSpeed{ 0 };
	//int health{ 1 };

	float lastJump = 1.0f;
	float lastCollidable = 1.0f;
	bool collidable = true;
	bool isJumping = false;

	float deathTimer = -10;

	class PhysicsComponent* physics{ nullptr };
	class TextureAnimationComponent* animation{ nullptr };
};