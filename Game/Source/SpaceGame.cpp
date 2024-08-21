#include "SpaceGame.h"
#include "Engine.h"

#include<memory>

bool SpaceGame::Initialize()
{
	rapidjson::Document document;
	Json::Load("Scenes/scene.json", document);

	m_scene = std::make_unique<Scene>(m_engine);
	m_scene->Read(document);
	m_scene->Initialize();

	ADD_OBSERVER(PlayerDead, SpaceGame::OnPlayerDead)
	ADD_OBSERVER(AddPoints, SpaceGame::OnAddPoints)

    return true;
}

void SpaceGame::Shutdown()
{
	m_scene->RemoveAll();
	
}

void SpaceGame::Update(float dt)
{
	m_scene->Update(m_engine->GetTime().GetDeltaTime());

}

void SpaceGame::Draw(Renderer& renderer)
{
	m_scene->Draw(m_engine->GetRenderer());
}

void SpaceGame::OnPlayerDead(const Event& event)
{
	std::cout << "Game Player Dead\n";
}

void SpaceGame::OnAddPoints(const Event& event)
{
	m_score += std::get<int>(event.data);
	std::cout << m_score << std::endl;
}
