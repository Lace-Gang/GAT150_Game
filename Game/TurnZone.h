#pragma once

#include "Components/Component.h"

class TurnZone : public Component
{
public:
	CLASS_DECLARATION(TurnZone);
	CLASS_PROTOTYPE(TurnZone);



private:
	int uncertainty{ 1 };

	// Inherited via Component
	void Initialize() override;
	void Update(float dt) override;
};