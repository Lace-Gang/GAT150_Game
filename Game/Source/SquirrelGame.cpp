#include "SquirrelGame.h"
#include "Engine.h"
#include "Framework/Actor.h"
#include "Components/AcornComponent.h"

#include<iostream>
#include<memory>

bool SquirrelGame::Initialize()
{
	rapidjson::Document document;
	Json::Load("Scenes/squirrel_scene.json", document);

	m_scene = std::make_unique<Scene>(m_engine);
	m_scene->Read(document);
	m_scene->Initialize();

	ADD_OBSERVER(PlayerDead, SquirrelGame::OnPlayerDead);
	ADD_OBSERVER(AddPoints, SquirrelGame::OnAddPoints);


	//std::unique_ptr<AcornComponent> acorn = std::make_unique<AcornComponent>(Factory::Instance().Create("AcornComponent"));
	//std::unique_ptr<Object> acorn = Factory::Instance().Create("AcornComponent");
	//std::unique_ptr<AcornComponent> acorn = dynamic_cast<std::unique_ptr<AcornComponent>*>(Factory::Instance().Create("AcornComponent"));
	//m_scene->AddActor(acorn);

	auto acorn = Factory::Instance().Create<Actor>("acorn");
	//acorn->transform.rotation = acorn->transform.rotation;
	acorn->transform.position.x = 100.0;
	acorn->transform.position.y = 150.0;
	//m_scene->AddActor(std::move(acorn), true);
	
	auto goldacorn = Factory::Instance().Create<Actor>("goldenacorn");
	//acorn->transform.rotation = acorn->transform.rotation;
	goldacorn->transform.position.x = 700.0;
	goldacorn->transform.position.y = 150.0;
	//m_scene->AddActor(std::move(goldacorn), true);

	auto enemy = Factory::Instance().Create<Actor>("enemy");
	//acorn->transform.rotation = acorn->transform.rotation;
	enemy->transform.position.x = 700.0;
	enemy->transform.position.y = 450.0;
	//m_scene->AddActor(std::move(enemy), true);
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
	m_scene->Update(m_engine->GetTime().GetDeltaTime());



}

void SquirrelGame::Draw(Renderer& renderer)
{
	m_scene->Draw(m_engine->GetRenderer());
}

void SquirrelGame::OnPlayerDead(const Event& event)
{
	//std::cout << "Game Player Dead\n";
	rapidjson::Document document;
	Json::Load("Scenes/game_over_scene.json", document);
	
	m_scene->RemoveAll();
	//
	//m_scene = std::make_unique<Scene>(m_engine);
	//m_scene->Read(document);
	//m_scene->Initialize();
}

void SquirrelGame::OnAddPoints(const Event& event)
{
	m_score += std::get<int>(event.data);
	std::cout << m_score << std::endl;

	std::string sScore = "Score: " + std::to_string(m_score);
	std::string sName = "scoreText";
	//ResourceManager
	//m_scene->
	//m_scene->GetActor(sName);
	//Scene::GetActor(sName);
}
