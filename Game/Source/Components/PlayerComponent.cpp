#include "PlayerComponent.h"
#include "Engine.h"
//#include "Components/Box2DPhysicsComponent.h"
//#include "Physics/RigidBody.h"
#include <iostream>

FACTORY_REGISTER(PlayerComponent)
void PlayerComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1);
}

void PlayerComponent::Update(float dt)
{
	//Vector2 direction{ 0, 0 };

	lastJump += dt;

	if (health <= 0)
	{
		EVENT_NOTIFY(PlayerDead);
	}


	float rotate = 0;
	float thrust = 0;
	//if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	//if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	//if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	//if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

	//if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	//if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) thrust = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) thrust = 1;

	Vector2 direction = Vector2{ 1, 0 }.Rotate(Math::DegToRad(owner->transform.rotation));

	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_W)) Jump();

	owner->GetComponent<PhysicsComponent>()->ApplyTorque(rotate * 90 * dt);
	owner->GetComponent<PhysicsComponent>()->ApplyForce(direction*speed * thrust);
	//	owner->GetComponent<PhysicsComponent>()->ApplyForce(direction*speed);


	//if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
	//{
	//	auto rocket = Factory::Instance().Create<Actor>("rocket");
	//
	//	rocket->transform.position = owner->transform.position;
	//	rocket->transform.rotation = owner->transform.rotation;
	//	owner->scene->AddActor(std::move(rocket), true);
	//
	//}


}

void PlayerComponent::OnCollisionEnter(Actor* actor)
{
	if (actor->tag == "enemy")
	{
		EVENT_NOTIFY(PlayerDead);
	}
	
	if (actor->tag == "acorn")
	{
		EVENT_NOTIFY_DATA(AddPoints, 100);
	}

}

void PlayerComponent::Jump()
{
	if (lastJump > 1)
	{
		lastJump = 0.0f;
		float thrust = 25000.0f;
		Vector2 directionUp = {0, -2};
		owner->GetComponent<PhysicsComponent>()->ApplyForce(directionUp * thrust);
		//owner->GetComponent<RigidBody>().shapeDef
	}
}

void PlayerComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void PlayerComponent::Write(json_t& value)
{
	//
}
