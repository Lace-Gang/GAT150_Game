#include "AcornComponent.h"
#include "Engine.h"
#include "Math/Random.h"
#include "PauseCollisionZone.h"


#include <iostream>



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
	//owner->GetComponent<PhysicsComponent>()->DiscriminantCollision();
}

void AcornComponent::Update(float dt)
{
	lastCollidable += dt;

	if (!collidable && lastCollidable > 0.2)
	{
		owner->GetComponent<PhysicsComponent>()->EnableCollision();
		collidable = true;
	}
}

void AcornComponent::OnCollisionEnter(Actor* actor)
{
	if (actor->tag == "PauseCollisionZone" && collidable)
	{
		//std::cout << "aaaa" << std::endl;
		//auto czone = dynamic_cast<Component*>(actor);
		//auto zone = dynamic_cast<PauseCollisionZone*>(czone);
		float chance = randomf(2);
		if (chance <= 1)
		{
			owner->GetComponent<PhysicsComponent>()->DisableCollision();
			lastCollidable = 0.0f;
			collidable = false;
		}

	}
	if (actor->tag == "water")
	{
		owner->destroyed = true;
	}

}

void AcornComponent::OnCollisionExit(Actor* actor)
{
	if (actor->tag == "PauseCollisionZone" && collidable)
	{
		
		owner->GetComponent<PhysicsComponent>()->EnableCollision();
		collidable = true;
		

	}
}

void AcornComponent::Read(const json_t& value)
{
	//
}

void AcornComponent::Write(json_t& value)
{
	//
}
