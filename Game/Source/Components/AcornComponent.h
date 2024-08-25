#pragma once

#include "Components/Component.h"

class AcornComponent : public Component
{
public:
	CLASS_DECLARATION(AcornComponent);
	CLASS_PROTOTYPE(AcornComponent);

	AcornComponent() = default;
	//AcornComponent(const AcornComponent& other, float x, float y);

	// Inherited via Component
	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);

private:
	float lastCollidable = 1.0f;
	bool collidable = true;

};