#include "SquirrelGame.h"
#include "Engine.h"
#include "Framework/Actor.h"
#include "Components/AcornComponent.h"

#include<iostream>
#include<memory>

bool SquirrelGame::Initialize()
{

	//innitializing the scene and all scene components
	m_scene = std::make_unique<Scene>(m_engine);
	//std::string sceneNames[] = { "Scenes/tilemap.json", "Scenes/squirrel_scene.json" };
	std::string sceneNames[] = { "Scenes/tilemap_2.json", "Scenes/squirrel_scene.json" };
	//std::string sceneNames[] = { "Scenes/squirrel_scene.json" };
	for (auto sceneName : sceneNames)
	{
		rapidjson::Document document;
		Json::Load(sceneName, document);
		m_scene->Read(document);

	}
	m_scene->Initialize();
	



	ADD_OBSERVER(PlayerDead, SquirrelGame::OnPlayerDead);
	ADD_OBSERVER(AddPoints, SquirrelGame::OnAddPoints);
	ADD_OBSERVER(PlayerChangeHealth, SquirrelGame::OnPlayerChangeHealth);

	



	//std::unique_ptr<AcornComponent> acorn = std::make_unique<AcornComponent>(Factory::Instance().Create("AcornComponent"));
	//std::unique_ptr<Object> acorn = Factory::Instance().Create("AcornComponent");
	//std::unique_ptr<AcornComponent> acorn = dynamic_cast<std::unique_ptr<AcornComponent>*>(Factory::Instance().Create("AcornComponent"));
	//m_scene->AddActor(acorn);

	auto acorn = Factory::Instance().Create<Actor>("acorn");
	//acorn->transform.rotation = acorn->transform.rotation;
	acorn->transform.position.x = 700.0;
	acorn->transform.position.y = 150.0;
	m_scene->AddActor(std::move(acorn), true);
	
	auto goldacorn = Factory::Instance().Create<Actor>("goldenacorn");
	//acorn->transform.rotation = acorn->transform.rotation;
	goldacorn->transform.position.x = 100.0;
	goldacorn->transform.position.y = 150.0;
	m_scene->AddActor(std::move(goldacorn), true);

	auto enemy = Factory::Instance().Create<Actor>("enemy");
	//acorn->transform.rotation = acorn->transform.rotation;
	enemy->transform.position.x = 700.0;
	enemy->transform.position.y = 450.0;
	m_scene->AddActor(std::move(enemy), true);
	//acorn->scene->AddActor(std::move(acorn), true);

	auto collisionZone = Factory::Instance().Create<Actor>("PauseCollisionZone");
	//acorn->transform.rotation = acorn->transform.rotation;
	//acorn->transform.position.x = 100.0;
	//acorn->transform.position.y = 150.0;
	m_scene->AddActor(std::move(collisionZone), true);





	return true;
}

void SquirrelGame::Shutdown()
{
	m_scene->RemoveAll();

}

void SquirrelGame::Update(float dt)
{
	switch (state)
	{
	case SquirrelGame::eState::Title:
			if (m_scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_SPACE))
			{
				state = eState::StartGame;
			}
		break;
	case SquirrelGame::eState::StartGame:
			m_score = 0;
			m_playerHealth = 1;
			state = eState::Game;
		break;
	case SquirrelGame::eState::StartLevel:
		break;
	case SquirrelGame::eState::Game:
		m_scene->Update(m_engine->GetTime().GetDeltaTime());
		break;
	case SquirrelGame::eState::PlayerDead:
			m_scene->RemoveAll();
			m_scene->Initialize();
		{
						   //Factory::Instance().Create<Actor>("<prototype name");
			auto deathText = Factory::Instance().Create<Actor>("Acorn");
			//deathText->transform.position.x = 100.0;
			//deathText->transform.position.y = 150.0;
			m_scene->AddActor(std::move(deathText), true);
		}
			state = eState::GameOver;
		break;
	case SquirrelGame::eState::GameOver:
			//m_scene->Update(m_engine->GetTime().GetDeltaTime());
		break;
	case SquirrelGame::eState::SetWin:
		//
		break;
	case SquirrelGame::eState::GameWon:
		//
		break;
	case SquirrelGame::eState::LevelTransition:
		//
		break;
	default:
		break;
	}



}

void SquirrelGame::Draw(Renderer& renderer)
{
	m_scene->Draw(m_engine->GetRenderer());
}

void SquirrelGame::OnPlayerDead(const Event& event)
{
	//state = eState::PlayerDead;
}

void SquirrelGame::OnPlayerChangeHealth(const Event& event)
{
	m_playerHealth += std::get<int>(event.data);
	
	std::string sScore = "Health: " + std::to_string(m_playerHealth);
	std::string sName = "healthText";
	
	auto actor = m_scene->GetActor<Actor>(sName);
	actor->GetComponent<TextComponent>()->SetText(sScore);
}



void SquirrelGame::OnAddPoints(const Event& event)
{
	m_score += std::get<int>(event.data);
	//std::cout << m_score << std::endl;

	std::string sScore = "Score: " + std::to_string(m_score);
	std::string sName = "scoreText";
	//ResourceManager
	//m_scene->
	//m_scene->GetActor<Actor>(sName);
	auto actor = m_scene->GetActor<Actor>(sName);
	actor->GetComponent<TextComponent>()->SetText(sScore);
	//m_scene->GetActo(sName);
	//Scene::GetActor(sName);
}
