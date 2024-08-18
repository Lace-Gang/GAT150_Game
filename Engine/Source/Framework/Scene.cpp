#include "Scene.h"
#include "Actor.h"
#include "Core/Factory.h"
#include "../Engine.h"
#include "../Renderer/Particle.h"
#include "../Renderer/Color.h"

#include<algorithm> //for remove_if

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

void Scene::AddActor(std::unique_ptr<Actor> actor)
{
	actor->scene = this;
	actors.push_back(std::move(actor));
}

void Scene::RemoveAll()
{
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

			AddActor(std::move(actor));
		}
	}
}

void Scene::Write(json_t& value)
{
	//
}