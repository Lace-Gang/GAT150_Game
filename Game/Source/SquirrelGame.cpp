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
	acorn->transform.position.x = 500.0;
	acorn->transform.position.y = 450.0;
	//m_scene->AddActor(std::move(acorn), true);
	//acorn->scene->AddActor(std::move(acorn), true);

	auto enemy = Factory::Instance().Create<Actor>("enemy");
	//acorn->transform.rotation = acorn->transform.rotation;
	enemy->transform.position.x = 700.0;
	enemy->transform.position.y = 450.0;
	//m_scene->AddActor(std::move(enemy), true);
	//acorn->scene->AddActor(std::move(acorn), true);


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
	std::cout << "Game Player Dead\n";
}

void SquirrelGame::OnAddPoints(const Event& event)
{
	m_score += std::get<int>(event.data);
	std::cout << m_score << std::endl;
}
