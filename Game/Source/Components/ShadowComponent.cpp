#include "ShadowComponent.h"

#include "PlayerComponent.h"
#include "Engine.h"
#include "Components/Box2DPhysicsComponent.h"
#include "Physics/RigidBody.h"
#include "Components/TextureAnimationComponent.h"
#include "Components/AudioComponent.h"

#include <iostream>s

FACTORY_REGISTER(ShadowComponent)
void ShadowComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&ShadowComponent::OnCollisionEnter, this, std::placeholders::_1);

	physics = owner->GetComponent<PhysicsComponent>();
	animation = owner->GetComponent<TextureAnimationComponent>();

	storedSpeed = speed;
}

void ShadowComponent::Update(float dt)
{
	
	

	if (owner->destroyed) return;

	if (!(deathTimer == -10)) deathTimer -= dt;
	lastJump += dt;
	lastCollidable += dt;

	if(deathTimer < 0 && deathTimer > -9) owner->destroyed = true;

	if (!collidable && lastCollidable > 0.2 && lastJump > 0.5)
	{
		isJumping = false;
		owner->GetComponent<PhysicsComponent>()->EnableCollision();
		collidable = true;
		speed = storedSpeed;
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

void ShadowComponent::OnCollisionEnter(Actor* actor)
{
	if (actor->tag == "water")
	{
		animation->SetAnimation("die");
		deathTimer = 0.5;
	}
	if (actor->tag == "acorn")
	{
		actor->destroyed = true;
		owner->GetComponent<AudioComponent>()->Play();
	}
	if (actor->tag == "goldenacorn")
	{
		actor->destroyed = true;
		owner->GetComponent<AudioComponent>()->Play();
	}

}

void ShadowComponent::Jump(float* speed)
{
	if (lastJump > 1)
	{
		isJumping = true;
		lastJump = 0.0f;
		animation->SetAnimation("jump");

		*speed *= 0.4;
		float thrust = 10000.0f;
		Vector2 directionUp = { 0.0, -3.0f };
		physics->ApplyForce(directionUp * thrust);

		physics->DisableCollision();
		lastCollidable = 0.0f;
		collidable = false;
	}
}

void ShadowComponent::JumpDown()
{
	isJumping = true;
	animation->SetAnimation("jump");
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
