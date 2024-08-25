#include "GroundComponent.h"
#include "Engine.h"


FACTORY_REGISTER(GroundComponent)

void GroundComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&GroundComponent::OnCollisionEnter, this, std::placeholders::_1);

}

void GroundComponent::Update(float dt)
{
	//owner->transform.position.x = 600;
	//owner->transform.position.y = 800;
}

void GroundComponent::OnCollisionEnter(Actor* actor)
{
	//
}

void GroundComponent::Read(const json_t& value)
{
	//
}

void GroundComponent::Write(json_t& value)
{
	//
}