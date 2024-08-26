#include "ShadowComponent.h"

#include "PlayerComponent.h"
#include "Engine.h"
#include "Components/Box2DPhysicsComponent.h"
#include "Physics/RigidBody.h"
#include "Components/TextureAnimationComponent.h"
#include <iostream>s

FACTORY_REGISTER(ShadowComponent)
void ShadowComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&ShadowComponent::OnCollisionEnter, this, std::placeholders::_1);

}

void ShadowComponent::Update(float dt)
{
	
	

	if (owner->destroyed) return;

	lastJump += dt;
	lastCollidable += dt;


	if (!collidable && lastCollidable > 0.2 && lastJump > 0.5)
	{
		owner->GetComponent<PhysicsComponent>()->EnableCollision();
		collidable = true;
	}

	if (!collidable && lastCollidable > 0.5 && lastJump > 0.5)
	{
		owner->GetComponent<PhysicsComponent>()->EnableCollision();
		collidable = true;
	}
	



	float rotate = 0;
	float thrust = 0;
	
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) thrust = 1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) thrust = -1;

	Vector2 direction = Vector2{ 1, 0 }.Rotate(Math::DegToRad(owner->transform.rotation));

	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_W)) Jump();
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_S)) JumpDown();

	owner->GetComponent<PhysicsComponent>()->ApplyTorque(rotate * 90 * dt);
	owner->GetComponent<PhysicsComponent>()->ApplyForce(direction * speed * thrust);
	


}

void ShadowComponent::OnCollisionEnter(Actor* actor)
{
	if (actor->tag == "acorn")
	{
		actor->destroyed = true;
	}
	if (actor->tag == "goldenacorn")
	{
		actor->destroyed = true;
	}

}

void ShadowComponent::Jump()
{
	if (lastJump > 1)
	{
		lastJump = 0.0f;
		float thrust = 25000.0f;
		Vector2 directionUp = { 0, -2 };
		owner->GetComponent<PhysicsComponent>()->ApplyForce(directionUp * thrust);
		owner->GetComponent<PhysicsComponent>()->DisableCollision();
		lastCollidable = 0.0f;
		collidable = false;
	}
}

void ShadowComponent::JumpDown()
{
	owner->GetComponent<PhysicsComponent>()->DisableCollision();
	lastCollidable = 0.0f;
	collidable = false;
}

void ShadowComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void ShadowComponent::Write(json_t& value)
{
	//
}
