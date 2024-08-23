#include "PlayerComponent.h"
#include "Engine.h"
#include <iostream>

FACTORY_REGISTER(PlayerComponent)
void PlayerComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1);
}

void PlayerComponent::Update(float dt)
{
	//Vector2 direction{ 0, 0 };

	float rotate = 0;
	float thrust = 0;
	//if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
	//if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;
	//if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
	//if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

	owner->GetComponent<PhysicsComponent>()->ApplyTorque(rotate * 90 * dt);
	Vector2 direction = Vector2{ 1, 0 }.Rotate(Math::DegToRad(owner->transform.rotation));
	owner->GetComponent<PhysicsComponent>()->ApplyForce(direction*speed * thrust);
	//	owner->GetComponent<PhysicsComponent>()->ApplyForce(direction*speed);


	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
	{
		auto rocket = Factory::Instance().Create<Actor>("rocket");

		rocket->transform.position = owner->transform.position;
		rocket->transform.rotation = owner->transform.rotation;
		owner->scene->AddActor(std::move(rocket), true);

	}

}

void PlayerComponent::OnCollisionEnter(Actor* actor)
{
	//std::cout << "Player hit\n";
	//; //other option, but I'll do the second option here
	EVENT_NOTIFY(PlayerDead);
	EVENT_NOTIFY_DATA(AddPoints, 100);
}

void PlayerComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void PlayerComponent::Write(json_t& value)
{
	//
}
