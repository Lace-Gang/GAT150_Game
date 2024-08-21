#pragma once

#include "Components/Component.h"

class RocketComponent : public Component
{
public:
	CLASS_DECLARATION(RocketComponent)
	CLASS_PROTOTYPE(RocketComponent)


		void Initialize() override;
	void Update(float dt) override;

	void OnCollisionEnter(Actor* actor);

	//void Read(const json_t& value);
	//void Write(json_t& value);

public:
	float speed{ 0 };
}; 
