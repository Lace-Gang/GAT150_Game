#pragma once
#include "Game.h"
#include "Event/Observer.h"

#include<memory>

//C++ lets you have more than one base class!
class SpaceGame : public Game, Observer
{
public:
	SpaceGame() = default;
	SpaceGame(Engine* engine) : Game{ engine } {}

	bool Initialize() override;
	void Shutdown() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;

	//events
	void OnPlayerDead(const class Event& event);
	void OnAddPoints(const Event& event);
		
private:
	std::unique_ptr<class Scene> m_scene;
};