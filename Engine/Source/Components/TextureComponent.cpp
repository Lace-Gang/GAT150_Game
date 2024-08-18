#include "TextureComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Engine.h"
#include "Resources/ResourceManager.h"


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
//	renderer.DrawTexture(texture.get() transform, true);
}

void TextureComponent::Read(const json_t& value)
{
	READ_DATA_REQUIRED(value, textureName);
}

void TextureComponent::Write(json_t& value)
{
	//To Do
}