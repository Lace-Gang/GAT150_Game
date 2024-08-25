#include "TextureComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Engine.h"
#include "Resources/ResourceManager.h"


FACTORY_REGISTER(TextureComponent)
void TextureComponent::Initialize()
{
	//To Do
	if (!textureName.empty())
	{
		texture = ResourceManager::Instance().Get<Texture>(textureName, owner->scene->engine->GetRenderer());
	}
}

void TextureComponent::Update(float dt)
{
	//To Do (Maybe)
}

void TextureComponent::Draw(Renderer& renderer)
{
	Transform transform = owner->transform;
	renderer.DrawTexture(texture, transform);
}

void TextureComponent::Draw(Renderer& renderer, bool mirrored)
{
	Transform transform = owner->transform;
	renderer.DrawTexture(texture, transform, mirrored);
}

void TextureComponent::Read(const json_t& value)
{
	READ_DATA_REQUIRED(value, textureName);
}

void TextureComponent::Write(json_t& value)
{
	//To Do
}