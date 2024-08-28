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
	m_DeadScreen = std::make_unique<Scene>(m_engine);
	m_TitleScreen = std::make_unique<Scene>(m_engine);
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


	std::string dSceneName= { "Scenes/player_dead.json" };
	rapidjson::Document dDocument;
	Json::Load(dSceneName, dDocument);
	m_DeadScreen->Read(dDocument);
	m_DeadScreen->Initialize();
	
	std::string tSceneName= { "Scenes/title_screen.json" };
	rapidjson::Document tDocument;
	Json::Load(tSceneName, tDocument);
	m_TitleScreen->Read(tDocument);
	m_TitleScreen->Initialize();

	


	ADD_OBSERVER(PlayerDead, SquirrelGame::OnPlayerDead);
	ADD_OBSERVER(AddPoints, SquirrelGame::OnAddPoints);
	ADD_OBSERVER(PlayerChangeHealth, SquirrelGame::OnPlayerChangeHealth);

	



	//std::unique_ptr<AcornComponent> acorn = std::make_unique<AcornComponent>(Factory::Instance().Create("AcornComponent"));
	//std::unique_ptr<Object> acorn = Factory::Instance().Create("AcornComponent");
	//std::unique_ptr<AcornComponent> acorn = dynamic_cast<std::unique_ptr<AcornComponent>*>(Factory::Instance().Create("AcornComponent"));
	//m_scene->AddActor(acorn);

	

	//auto enemy = Factory::Instance().Create<Actor>("enemy");
	////acorn->transform.rotation = acorn->transform.rotation;
	//enemy->transform.position.x = 300.0;
	//enemy->transform.position.y = 150.0;
	//m_scene->AddActor(std::move(enemy), true);
	//acorn->scene->AddActor(std::move(acorn), true);

	//auto collisionZone = Factory::Instance().Create<Actor>("PauseCollisionZone");
	//acorn->transform.rotation = acorn->transform.rotation;
	//acorn->transform.position.x = -100.0;
	//acorn->transform.position.y = 150.0;
	//m_scene->AddActor(std::move(collisionZone), true);





	return true;
}

void SquirrelGame::Shutdown()
{
	m_scene->RemoveAll(true);
	m_DeadScreen->RemoveAll(true); 
	m_TitleScreen->RemoveAll(true);

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
			state = eState::StartLevel;
		break;
	case SquirrelGame::eState::StartLevel:
			
			LoadActors();

			state = eState::Game;
		break;
	case SquirrelGame::eState::Game:
		m_scene->Update(m_engine->GetTime().GetDeltaTime());
		break;
	case SquirrelGame::eState::PlayerDead:
	{
			auto actor = m_scene->GetActor<Actor>("music");
			actor->GetComponent<AudioComponent>()->Stop();
	}

			m_scene->RemoveAll();
		{
			std::string sScore = "Score: " + std::to_string(m_score);
			std::string sName = "scoreText";
			auto actor = m_DeadScreen->GetActor<Actor>(sName);
			actor->GetComponent<TextComponent>()->SetText(sScore);
		}

			state = eState::GameOver;
		break;
	case SquirrelGame::eState::GameOver:
			m_DeadScreen->Update(m_engine->GetTime().GetDeltaTime());
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

	if (m_scene->engine->GetInput().GetKeyDown(SDL_SCANCODE_X))
	{
		auto enemy = Factory::Instance().Create<Actor>("acorn");
		//acorn->transform.rotation = acorn->transform.rotation;
		enemy->transform.position.x = 100.0;
		enemy->transform.position.y = 0.0;
		m_scene->AddActor(std::move(enemy), true);
	}

}

void SquirrelGame::Draw(Renderer& renderer)
{
	switch (state)
	{
	case SquirrelGame::eState::Title:
		m_TitleScreen->Draw(m_engine->GetRenderer());
		break;
	case SquirrelGame::eState::StartGame:
		break;
	case SquirrelGame::eState::StartLevel:
		break;
	case SquirrelGame::eState::Game:
		m_scene->Draw(m_engine->GetRenderer());
		break;
	case SquirrelGame::eState::PlayerDead:
		break;
	case SquirrelGame::eState::GameOver:
		m_DeadScreen->Draw(m_engine->GetRenderer());
		break;
	case SquirrelGame::eState::SetWin:
		break;
	case SquirrelGame::eState::GameWon:
		break;
	case SquirrelGame::eState::LevelTransition:
		break;
	default:
		break;
	}
}

void SquirrelGame::LoadActors()
{
	{
		auto acorn = Factory::Instance().Create<Actor>("acorn");
		//acorn->transform.rotation = acorn->transform.rotation;
		acorn->transform.position.x = 700.0;
		acorn->transform.position.y = 150.0;
		m_scene->AddActor(std::move(acorn), true);

		auto goldacorn = Factory::Instance().Create<Actor>("goldenacorn");
		//acorn->transform.rotation = acorn->transform.rotation;
		goldacorn->transform.position.x = 90.0;
		goldacorn->transform.position.y = 150.0;
		m_scene->AddActor(std::move(goldacorn), true);

		auto goldacorn2 = Factory::Instance().Create<Actor>("goldenacorn");
		//acorn->transform.rotation = acorn->transform.rotation;
		goldacorn2->transform.position.x = 790.0;
		goldacorn2->transform.position.y = 150.0;
		m_scene->AddActor(std::move(goldacorn2), true);

		auto tz_1 = Factory::Instance().Create<Actor>("turnzone");
		tz_1->transform.position.x = 350.0;
		tz_1->transform.position.y = 550.0;
		m_scene->AddActor(std::move(tz_1), true);
		auto tz_2 = Factory::Instance().Create<Actor>("turnzone");
		tz_2->transform.position.x = 950.0;
		tz_2->transform.position.y = 550.0;
		m_scene->AddActor(std::move(tz_2), true);
		auto tz_3 = Factory::Instance().Create<Actor>("turnzone");
		tz_3->transform.position.x = 450.0;
		tz_3->transform.position.y = 300.0;
		m_scene->AddActor(std::move(tz_3), true);
		auto tz_4 = Factory::Instance().Create<Actor>("turnzone");
		tz_4->transform.position.x = 850.0;
		tz_4->transform.position.y = 300.0;
		m_scene->AddActor(std::move(tz_4), true);

		auto pc_1 = Factory::Instance().Create<Actor>("PauseCollisionZone");
		pc_1->transform.position.x = 0.0;
		pc_1->transform.position.y = 170.0;
		m_scene->AddActor(std::move(pc_1), true);
		auto pc_2 = Factory::Instance().Create<Actor>("PauseCollisionZone");
		pc_2->transform.position.x = 50.0;
		pc_2->transform.position.y = 170.0;
		m_scene->AddActor(std::move(pc_2), true);
		auto pc_3 = Factory::Instance().Create<Actor>("PauseCollisionZone");
		pc_3->transform.position.x = 100.0;
		pc_3->transform.position.y = 170.0;
		m_scene->AddActor(std::move(pc_3), true);

		auto enemy = Factory::Instance().Create<Actor>("enemy");
		enemy->transform.position.x = 450.0;
		enemy->transform.position.y = 500.0;
		m_scene->AddActor(std::move(enemy), true);
		auto enemy2 = Factory::Instance().Create<Actor>("enemy");
		enemy2->transform.position.x = 500.0;
		enemy2->transform.position.y = 270.0;
		m_scene->AddActor(std::move(enemy2), true);

		auto shadow = Factory::Instance().Create<Actor>("shadow");
		shadow->transform.position.x = 1000.0;
		shadow->transform.position.y = 100.0;
		m_scene->AddActor(std::move(shadow), true);
	}
}

void SquirrelGame::OnPlayerDead(const Event& event)
{
	state = eState::PlayerDead;
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
