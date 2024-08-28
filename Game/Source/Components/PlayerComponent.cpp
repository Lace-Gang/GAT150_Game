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
	owner->OnCollisionExit= std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1);
	//auto idle = Factory::Instance().Create<TextureAnimationComponent>("textures/player-idle.png");
	//owner->AddComponent( ResourceManager::Instance().Get("player-idle", null));
	//for(auto components : owner->GetComponent(TextureAnimationComponent))
	//{
	//
	//}
	//owner->GetComponent<TextureComponent>();
//	owner->GetComponent<PhysicsComponent>()->EnableCollision();

	std::cout << health << std::endl;

	physics = owner->GetComponent<PhysicsComponent>();
	animation = owner->GetComponent<TextureAnimationComponent>();

	storedSpeed = speed;

}

void PlayerComponent::Update(float dt)
{
	//bool onGround = (groundCount > 0);


	if (health <= 0)
	{
		animation->SetAnimation("die");
		EVENT_NOTIFY(PlayerDead);
		owner->destroyed;
		return;
	}

	//if (owner->destroyed) return;

	lastJump += dt;
	lastCollidable += dt;


	if (!collidable && lastCollidable > 0.3  && lastJump > 0.6)
	{
		isJumping = false;
		physics->EnableCollision();
		collidable = true;
		speed = storedSpeed;
		//std::cout << "fixed speed" << std::endl;
	}

	//if (!collidable && lastCollidable > 0.5 && lastJump > 0.5)
	//{
	//	physics->EnableCollision();
	//	collidable = true;
	//	
	//}



	float rotate = 0;
	float thrust = 0;
	
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) thrust = -1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) thrust = 1;

	Vector2 direction = Vector2{ 1, 0 }.Rotate(Math::DegToRad(owner->transform.rotation));

	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_W)) Jump(&speed);
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_S)) JumpDown();

	physics->ApplyForce(direction * speed * thrust);
	//physics->ApplyForce(Vector2{ 0, -1000 });
	//float modifier = (onGround) ? : 0.2f;

	if (Math::Abs(physics->velocity.x) > 0.1f && !isJumping) animation->SetAnimation("run");
	else if(!isJumping) animation->SetAnimation("idle");
}

void PlayerComponent::OnCollisionEnter(Actor* actor)
{
	if (actor->tag == "enemy" || actor->tag == "shadow")
	{
		health -= 1;
		EVENT_NOTIFY_DATA(PlayerChangeHealth, -1);
	}
	if (actor->tag == "water")
	{
		EVENT_NOTIFY_DATA(PlayerChangeHealth, -health);
		health -= health;
		animation->SetAnimation("die");
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
		EVENT_NOTIFY_DATA(PlayerChangeHealth, 1);
		EVENT_NOTIFY_DATA(AddPoints, 200);
		std::cout << health << std::endl;
	}

	if (actor->tag == "Ground")
	{
		//std::cout << "test 1" << std::endl;
		if (actor->transform.position.y < owner->transform.position.y)
		{
			//std::cout << "test 2" << std::endl;
			//float placement = actor->transform.position.y - 100000;
			//owner->transform.position.y += 1200;
			//placement -= owner->GetComponent<Box2DPhysicsC>
			//while (actor->transform.position.y < owner->transform.position.y)
			//{
			//	std::cout << "test 3" << std::endl;
			//	owner->transform.position.y-=100;
			//}
		}
	}

}

void PlayerComponent::OnCollisionExit(Actor* actor)
{
	//if (actor->tag == "Ground") groundCount++;
}

void PlayerComponent::Jump(float* speed)
{
	if (lastJump > 1)
	{
		isJumping = true;
		lastJump = 0.0f;
		animation->SetAnimation("jump");

		*speed *= 0.4;
		//float thrust = 25000.0f;
		//float thrust = 4000.0f;
		float thrust = 10000.0f;
		Vector2 directionUp = {0.0, -3.0f};
		physics->ApplyForce(directionUp * thrust);
		//owner->GetComponent<RigidBody>()->DisableCollision();

		physics->DisableCollision();
		lastCollidable = 0.0f;
		collidable = false;
		//owner->GetComponent<RigidBody>().shapeDef
	}
}

void PlayerComponent::JumpDown()
{
	isJumping = true;
	animation->SetAnimation("jump");
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
