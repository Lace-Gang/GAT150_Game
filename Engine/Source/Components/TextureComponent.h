#pragma once

#include "RenderComponent.h"
#include "Renderer/Texture.h"

//#include<string>

class TextureComponent : public RenderComponent
{
public:
	CLASS_DECLARATION(TextureComponent)
	CLASS_PROTOTYPE(TextureComponent)


	// Inherited via RenderComponent
	void Initialize() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;
	void Draw(Renderer& renderer, bool mirrored) override;

public:
	Rect source;
	std::string textureName;
	res_t<Texture> texture;
};