#pragma once

#include "Object.h"
#include "../Renderer/Particle.h"

#include <list>
#include<memory>

class Renderer;
class Actor;
class Game;
class Engine;

class Scene : public Object
{
public:
	Scene(Engine* engine, Game* game = nullptr) : 
		engine{ engine },
		game{ game } {}

	Scene(const Scene& other);

	CLASS_DECLARATION(Scene)
	CLASS_PROTOTYPE(Scene)
	;;;;;;; //funny thing is you can put as many as you want and it's fine. I'll take this out later

	void Initialize() override;

	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddActor(std::unique_ptr<Actor> actor, bool initialize = false);
	void RemoveAll();

	void AddParticles(Actor* actor);

	template<typename T> T* GetActor();
	template<typename T> T* GetActor(const std::string& name);


public:
	Engine* engine{ nullptr };
	Game* game{ nullptr };

protected:
	std::list<std::unique_ptr<Actor>> actors;
	std::list<Particle*> m_particles;


};

//Template must be in the header, CANNOT be in the cpp
	template<typename T>
	T* Scene::GetActor()
	{
		for (auto& actor : actors)
		{
			T* result = dynamic_cast<T*>(actor.get()); 
			if (result) return result;
		}

		return nullptr;
	}

	template<typename T>
	inline T* Scene::GetActor(const std::string& name)
	{
		for (auto& actor : actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result && IsEqualIgnoreCase(result->name, name)) return result;
		}

		return nullptr;
	}

