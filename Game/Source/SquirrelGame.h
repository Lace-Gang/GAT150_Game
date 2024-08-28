#pragma once

#include "Game.h"
#include "Event/Observer.h"
#include "Framework/Scene.h"
#include "Components/AudioComponent.h"
#include<memory>

//C++ lets you have more than one base class!
class SquirrelGame : public Game, Observer
{
public:
	enum class eState : char //this saves memory (4 bytes to 1 byte)
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOver,
		SetWin,
		GameWon,
		LevelTransition
	};


	SquirrelGame() = default;
	SquirrelGame(Engine* engine) : Game{ engine } {}

	bool Initialize() override;
	void Shutdown() override;
	void Update(float dt) override;
	void Draw(Renderer& renderer) override;
	void LoadActors();

	//events
	void OnPlayerDead(const struct Event& event);
	void OnPlayerChangeHealth(const struct Event& event);
	void OnAddPoints(const Event& event);

public:
	int m_playerHealth = 1;

	float acorn_timer = 0.0f;

private:
	std::unique_ptr<class Scene> m_scene;
	std::unique_ptr<class Scene> m_TitleScreen;
	std::unique_ptr<class Scene> m_DeadScreen;
	eState state = eState::Title;
};