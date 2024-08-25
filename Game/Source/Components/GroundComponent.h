#pragma once

#include "Components/Component.h"

class GroundComponent : public Component
{
public:
	CLASS_DECLARATION(GroundComponent);
	CLASS_PROTOTYPE(GroundComponent);

	// Inherited via Component
	void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);

private:
};

