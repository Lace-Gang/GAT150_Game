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

public:
	std::string textureName;
	res_t<Texture> texture;
};