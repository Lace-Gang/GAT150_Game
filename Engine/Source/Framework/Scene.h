#pragma once
#include "../Renderer/Particle.h"

#include <list>
#include<memory>

class Renderer;
class Actor;
class Game;

class Scene
{
public:
	Scene() = default;
	Scene(Game* game) : m_game{ game } {}

	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddActor(std::unique_ptr<Actor> actor);
	void RemoveAll();

	void AddParticles(Actor* actor);

	template<typename T>
	T* GetActor();

	Game* GetGame() { return m_game; }

protected:
	std::list<std::unique_ptr<Actor>> m_actors;
	std::list<Particle*> m_particles;

	Game* m_game{ nullptr };

};

//Template must be in the header, CANNOT be in the cpp
	template<typename T>
	T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get()); 
			if (result) return result;
		}

		return nullptr;
	}

