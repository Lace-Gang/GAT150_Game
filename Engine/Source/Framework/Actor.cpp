#include "Actor.h"
//#include "../Renderer/Model.h" 
#include "../Components/RenderComponent.h"
#include "Core/Factory.h"



void Actor::Initialize()
{
	for (auto& component : components) 
	{
		component->Initialize();
	}
}

void Actor::Update(float dt)
{
	//check for lifespan
	if (lifespan != 0)
	{
		lifespan -= dt;
		//m_lifespan - dt;
		if (lifespan <= 0)
		{
			destroyed = true;
		}
	}

	for (auto& component : components) //can't copy a unique pointer, but can reference it "auto" vs "auto&"
	{
		component->Update(dt);
	}

	//transform.position += (m_velocity * dt);
	//m_velocity *= 1.0f /(1.0f + m_damping * dt);
}

void Actor::Draw(Renderer& renderer)
{
	if (destroyed) return;

	for (auto& component : components) //can't copy a unique pointer, but can reference it "auto" vs "auto&"
	{
		//dynamic casting to check for only rendercomponents
		RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component.get());
		if (renderComponent)
		{
			renderComponent->Draw(renderer);

		}
	}

	//if (m_model)
	//{
	//	m_model->Draw(renderer, m_transform);
	//}
}

void Actor::AddComponent(std::unique_ptr<Component> component)
{
	component->owner = this;
	components.push_back(std::move(component));
}



void Actor::Read(const json_t& value)
{
	Object::Read(value);

	READ_DATA(value, tag);
	READ_DATA(value, lifespan);

	if (HAS_DATA(value, transform)) transform.Read(GET_DATA(value, transform)); 
	//without doing it that way, transform will not find the keys for position, rotaion or scale because the only visible keys would be name and transform

	//read components
	if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray())
	{
		for (auto& componentValue : GET_DATA(value, components).GetArray())
		{
			std::string type;
			READ_DATA(componentValue, type);

			auto component = Factory::Instance().Create<Component>(type);
			component->Read(componentValue);

			AddComponent(std::move(component));
		}
	}
}

void Actor::Write(json_t& value)
{
	//To Do
}