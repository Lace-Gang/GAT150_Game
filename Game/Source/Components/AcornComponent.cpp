#include "AcornComponent.h"
#include "Engine.h"



FACTORY_REGISTER(AcornComponent);

//AcornComponent::AcornComponent(const AcornComponent& other, float x, float y)
//{
//	owner->transform.position.x = x;
//	owner->transform.position.y = y;
//	owner->transform.scale = other.owner->transform.scale;
//	owner->transform.rotation = other.owner->transform.rotation;
//}

void AcornComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&AcornComponent::OnCollisionEnter, this, std::placeholders::_1);
}

void AcornComponent::Update(float dt)
{
	//
}

void AcornComponent::OnCollisionEnter(Actor* actor)
{
	//
}

void AcornComponent::Read(const json_t& value)
{
	//
}

void AcornComponent::Write(json_t& value)
{
	//
}
