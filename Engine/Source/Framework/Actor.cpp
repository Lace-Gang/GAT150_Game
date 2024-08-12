#include "Actor.h"
//#include "../Renderer/Model.h" 
#include "../Components/RenderComponent.h"



void Actor::Initialize()
{
	for (auto& component : m_components) 
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
			m_destroyed = true;
		}
	}

	for (auto& component : m_components) //can't copy a unique pointer, but can reference it "auto" vs "auto&"
	{
		component->Update(dt);
	}

	m_transform.position += (m_velocity * dt);
	m_velocity *= 1.0f /(1.0f + m_damping * dt);
}

void Actor::Draw(Renderer& renderer)
{
	if (m_destroyed) return;

	for (auto& component : m_components) //can't copy a unique pointer, but can reference it "auto" vs "auto&"
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
	m_components.push_back(std::move(component));
}



void Actor::Read(const json_t& value)
{
	Object::Read(value);

	READ_DATA(value, tag);
	READ_DATA(value, lifespan);
}

void Actor::Write(json_t& value)
{
	//To Do
}