#include "Scene.h"
#include "Actor.h"
#include "Core/Factory.h"
#include "../Engine.h"
#include "../Renderer/Particle.h"
#include "../Renderer/Color.h"
#include "Components/CollisionComponent.h"
#include "Core/EAssert.h"

#include<algorithm> //for remove_if
#include<memory>



Scene::Scene(const Scene& other)
{
	ASSERT(false);
	//if someone tries to copy scene, it will crash. This is called a "hack"
}

void Scene::Initialize()
{
	for (auto& actor : actors)
	{
		actor->Initialize();

	}
}



void Scene::Update(float dt)
{
	//update

	for (auto& actor : actors)
	{
		if(actor->active) actor->Update(dt);

	}


	// collision
	for (auto& actor1 : actors)
	{
		CollisionComponent* collision1 = actor1->GetComponent<CollisionComponent>();
		if (!collision1) continue;

		for (auto& actor2 : actors)
		{
			// don't check with self
			if (actor1 == actor2) continue;

			CollisionComponent* collision2 = actor2->GetComponent<CollisionComponent>();
			if (!collision2) continue;

			if (collision1->CheckCollision(collision2))
			{
				if (actor1->OnCollisionEnter) actor1->OnCollisionEnter(actor2.get());
				if (actor2->OnCollisionEnter) actor2->OnCollisionEnter(actor1.get());
			}
		}
	}

	//destroy
	//c++ doesn't like when you destroy items in a list while in a for each.
	//so we will be using an itterator
	
	//std::list<Actor*>::iterator iter = m_actors.begin(); (great place to use auto instead)
	auto iter = actors.begin();
	while (iter != actors.end())
	{
		iter = ((*iter)->destroyed) ? actors.erase(iter) : ++iter; //if iter is destroyed,erase itter. Else ++itter
		//itter++ means to do the ++ after the line (postfix) ++itter means do ++ IN the line (prefix)
	}


	//this next line can be done in the 2022 verson of c++
	std::erase_if(actors, [](auto& actor) { return actor->destroyed; });

}

void Scene::Draw(Renderer& renderer)
{
	for (auto& actor : actors)
	{
		if(actor->active) actor->Draw(renderer);
	}
	
}

void Scene::AddActor(std::unique_ptr<Actor> actor, bool initialize)
{
	actor->scene = this;
	if (initialize) actor->Initialize();

	actors.push_back(std::move(actor));
}

void Scene::RemoveAll()
{
	//for (auto& actor : actors)
	//{
	//	actor.get_deleter();
	//	//actor->destroyed = true;
	//}
	actors.clear();
}


void Scene::Read(const json_t& value)
{
	if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray())
	{
		for (auto& actorValue : GET_DATA(value, actors).GetArray())
		{
			auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
			actor->Read(actorValue);

			bool prototype = false;
			READ_DATA(actorValue, prototype);

			if (prototype)
			{
				std::string  name = actor->name;
				Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor)); //things are taken right to left so name has to be stored elsewhere
			}
			else
			{
				AddActor(std::move(actor));
			}

			//AddActor(std::move(actor));
		}
	}
}

void Scene::Write(json_t& value)
{
	//
}