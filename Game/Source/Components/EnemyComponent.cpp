#include "EnemyComponent.h"

#include "Engine.h"
#include "Components/TextureAnimationComponent.h"
#include<iostream>


FACTORY_REGISTER(EnemyComponent);


void EnemyComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&EnemyComponent::OnCollisionEnter, this, std::placeholders::_1);

	physics = owner->GetComponent<PhysicsComponent>();
	animation = owner->GetComponent<TextureAnimationComponent>();

	storedSpeed = speed;
}

void EnemyComponent::Update(float dt)
{



	if (owner->destroyed) return;

	//if (!(deathTimer == -10)) deathTimer -= dt;
	lastJump += dt;
	lastCollidable += dt;

	//if (deathTimer < 0 && deathTimer > -9) owner->destroyed = true;

	if (!collidable && lastCollidable > 0.2 && lastJump > 0.5)
	{
		isJumping = false;
		owner->GetComponent<PhysicsComponent>()->EnableCollision();
		collidable = true;
		speed = storedSpeed;
		std::cout << "fixed speed" << std::endl;
	}

	//if (!collidable && lastCollidable > 0.5 && lastJump > 0.5)
	//{
	//	owner->GetComponent<PhysicsComponent>()->EnableCollision();
	//	collidable = true;
	//}




	float rotate = 0;
	float thrust = 0;

	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_A)) thrust = 1;
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_D)) thrust = -1;

	Vector2 direction = Vector2{ 1, 0 }.Rotate(Math::DegToRad(owner->transform.rotation));

	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_W)) Jump(&speed);
	if (owner->scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_S)) JumpDown();

	owner->GetComponent<PhysicsComponent>()->ApplyTorque(rotate * 90 * dt);
	owner->GetComponent<PhysicsComponent>()->ApplyForce(direction * speed * thrust);


	if (Math::Abs(physics->velocity.x) > 0.1f && !isJumping) animation->SetAnimation("run");
	else if (!isJumping) animation->SetAnimation("idle");
}

void EnemyComponent::OnCollisionEnter(Actor* actor)
{
	if (actor->tag == "water")
	{
		animation->SetAnimation("die");
		//deathTimer = 0.5;
	}
	if (actor->tag == "acorn")
	{
		actor->destroyed = true;
	}
	if (actor->tag == "goldenacorn")
	{
		actor->destroyed = true;
	}

}

void EnemyComponent::Jump(float* speed)
{
	if (lastJump > 1)
	{
		isJumping = true;
		lastJump = 0.0f;
		animation->SetAnimation("jump");

		*speed *= 0.4;
		float thrust = 10000.0f;
		Vector2 directionUp = { 0.0, -2.5f };
		physics->ApplyForce(directionUp * thrust);

		physics->DisableCollision();
		lastCollidable = 0.0f;
		collidable = false;
	}
}

void EnemyComponent::JumpDown()
{
	isJumping = true;
	animation->SetAnimation("jump");
	owner->GetComponent<PhysicsComponent>()->DisableCollision();
	lastCollidable = 0.0f;
	collidable = false;
}

void EnemyComponent::Read(const json_t& value)
{
	READ_DATA(value, speed);
}

void EnemyComponent::Write(json_t& value)
{
	//
}



//void EnemyComponent::Initialize()
//{
//	owner->OnCollisionEnter = std::bind(&EnemyComponent::OnCollisionEnter, this, std::placeholders::_1);
//	//std::cout << owner->tag << std::endl;
//
//	physics = owner->GetComponent<PhysicsComponent>();
//	animation = owner->GetComponent<TextureAnimationComponent>();
//
//	storedSpeed = speed;
//}
//
//void EnemyComponent::Update(float dt)
//{
//	lastJump += dt;
//
//	//float rotate = 0;
//	
//
//	Vector2 direction = Vector2{ 1, 0 }.Rotate(Math::DegToRad(owner->transform.rotation));
//	//owner->GetComponent<PhysicsComponent>()->ApplyTorque(rotate * 90 * dt);
//	owner->GetComponent<PhysicsComponent>()->ApplyForce(direction * speed * thrust);
//}
//
//void EnemyComponent::OnCollisionEnter(Actor* actor)
//{
//	if (actor->tag == "turnzone") thrust *= -1;
//}
//
//void EnemyComponent::Run()
//{
//	//
//}
//
//void EnemyComponent::Jump()
//{
//	//
//}
//
//void EnemyComponent::Read(const json_t& value)
//{
//	READ_DATA(value, speed);
//}
//
//void EnemyComponent::Write(json_t& value)
//{
//	//
//}