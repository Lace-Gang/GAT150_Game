#pragma once
#include "Component.h"
//#include "Renderer/Renderer.h"

class RenderComponent : public Component
{
public:
	virtual void Draw(class Renderer& renderer) = 0;
	virtual void Draw(class Renderer& renderer, bool mirrored) = 0;
};