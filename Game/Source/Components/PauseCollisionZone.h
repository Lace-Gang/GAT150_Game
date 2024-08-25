#pragma once


#include "Components/Component.h"

class PauseCollisionZone : public Component
{
public:
	CLASS_DECLARATION(PauseCollisionZone);
	CLASS_PROTOTYPE(PauseCollisionZone);


	// Inherited via Component
	void Initialize() override;
	void Update(float dt) override;


public:
	int uncertainty{ 1 };
};