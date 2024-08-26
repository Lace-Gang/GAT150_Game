#include "TextureComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Engine.h"
#include "Resources/ResourceManager.h"

#include<iostream>


FACTORY_REGISTER(TextureComponent)
void TextureComponent::Initialize()
{
	//To Do
	if (!textureName.empty())
	{
		texture = ResourceManager::Instance().Get<Texture>(textureName, owner->scene->engine->GetRenderer());
	}

	if (texture && source.w == 0 && source.h == 0)
	{
		source.x = 0;
		source.y = 0;

		source.w = (int)texture->GetSize().x;
		source.h = (int)texture->GetSize().y;
	}

}

void TextureComponent::Update(float dt)
{
	//To Do (Maybe) (Probably not. Not much point to one here)
}

void TextureComponent::Draw(Renderer& renderer)
{
	//std::cout << "aaaa" << std::endl;
	Transform transform = owner->transform;
	renderer.DrawTexture(texture, transform, source);
}

void TextureComponent::Draw(Renderer& renderer, bool mirrored)
{
	Transform transform = owner->transform;
	renderer.DrawTexture(texture, transform, source, mirrored);
}

void TextureComponent::Read(const json_t& value)
{
	READ_DATA_REQUIRED(value, textureName);
	READ_DATA(value, source);
}

void TextureComponent::Write(json_t& value)
{
	//To Do
}