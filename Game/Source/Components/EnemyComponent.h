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
	void Jump(float* speed);
	void JumpDown();

public:
	float speed{ 0 };
	float storedSpeed{ 0 };
	int health{ 1 };
	float thrust{ 1 };

	float lastJump = 1.0f;
	float lastCollidable = 1.0f;
	bool collidable = true;
	bool isJumping = false;

	int groundCount{ 0 };

	class PhysicsComponent* physics{ nullptr };
	class TextureAnimationComponent* animation{ nullptr };
};

