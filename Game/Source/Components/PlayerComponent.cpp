#include "PlayerComponent.h"
#include "Engine.h"
#include "Components/Box2DPhysicsComponent.h"
#include "Physics/RigidBody.h"
#include "Components/TextureAnimationComponent.h"
#include <iostream>s

FACTORY_REGISTER(PlayerComponent)
void PlayerComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1);
	//auto idle = Factory::Instance().Create<TextureAnimationComponent>("textures/player-idle.png");
	//owner->AddComponent( ResourceManager::Instance().Get("player-idle", null));
	//for(auto components : owner->GetComponent(TextureAnimationComponent))
	//{
	//
	//}
	//owner->GetComponent<TextureComponent>();
//	owner->GetComponent<PhysicsComponent>()->EnableCollision();

	std::cout << health << std::endl;

}

void PlayerComponent::Update(float dt)
{
	//Vector2 direction{ 0, 0 };


	if (health <= 0)
	{
		EVENT_NOTIFY(PlayerDead);
		owner->destroyed;
		return;
	}

	if (owner->destroyed) return;

	lastJump += dt;
	lastCollidable += dt;


	if (!collidable && lastCollidable > 0.2  && lastJump > 0.5)
	{
		owner->GetComponent<PhysicsComponent>()->EnableCollision();
		collidable = true;
	}

	if (!collidable && lastCollidable > 0.5 && lastJump > 0.5)
	{
		owner->GetComponent<PhysicsComponent>()->EnableCollision();
		collidable = true;
	}
	//if (collidable && lastJump > 0.5) owner;
	//b2Contact::SetEnabled(true);



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
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_S)) JumpDown();

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
		health -= 1;
	}
	
	if (actor->tag == "acorn")
	{
		actor->destroyed = true;
		EVENT_NOTIFY_DATA(AddPoints, 100);
	}
	if (actor->tag == "goldenacorn")
	{
		actor->destroyed = true;
		health += 1;
		EVENT_NOTIFY_DATA(AddPoints, 200);
		std::cout << health << std::endl;
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
		//owner->GetComponent<RigidBody>()->DisableCollision();
		owner->GetComponent<PhysicsComponent>()->DisableCollision();
		lastCollidable = 0.0f;
		collidable = false;
		//owner->GetComponent<RigidBody>().shapeDef
	}
}

void PlayerComponent::JumpDown()
{
	owner->GetComponent<PhysicsComponent>()->DisableCollision();
	lastCollidable = 0.0f;
	collidable = false;
}

void PlayerComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void PlayerComponent::Write(json_t& value)
{
	//
}
