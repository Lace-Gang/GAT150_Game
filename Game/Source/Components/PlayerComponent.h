#pragma once

#include "Components/Component.h"

class PlayerComponent : public Component
{
public:
	CLASS_DECLARATION(PlayerComponent)

	void Initialize() override;
	void Update(float dt) override;

	//void Read(const json_t& value);
	//void Write(json_t& value);

public:
	float speed{ 0 };
};