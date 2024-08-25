#include "EnemyComponent.h"

#include "Engine.h"
#include<iostream>


FACTORY_REGISTER(EnemyComponent);


void EnemyComponent::Initialize()
{
	owner->OnCollisionEnter = std::bind(&EnemyComponent::OnCollisionEnter, this, std::placeholders::_1);
	//std::cout << owner->tag << std::endl;
}

void EnemyComponent::Update(float dt)
{
	lastJump += dt;

	//float rotate = 0;
	

	Vector2 direction = Vector2{ 1, 0 }.Rotate(Math::DegToRad(owner->transform.rotation));
	//owner->GetComponent<PhysicsComponent>()->ApplyTorque(rotate * 90 * dt);
	owner->GetComponent<PhysicsComponent>()->ApplyForce(direction * speed * thrust);
}

void EnemyComponent::OnCollisionEnter(Actor* actor)
{
	if (actor->tag == "turnzone") thrust *= -1;
}

void EnemyComponent::Run()
{
	//
}

void EnemyComponent::Jump()
{
	//
}

void EnemyComponent::Read(const json_t& value)
{
	//
}

void EnemyComponent::Write(json_t& value)
{
	//
}