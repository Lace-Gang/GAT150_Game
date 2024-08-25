#pragma once

// ** core **
#include "Core/EAssert.h"
#include "Core/ETimer.h"
#include "Core/EFile.h"
#include "Core/EString.h"
#include "Core/Json.h"
#include "Core/Singleton.h"
#include "Core/Factory.h"


// ** systems **
//renderer
#include "Renderer/Renderer.h" 
#include "Renderer/Particle.h"
#include "Renderer/ParticleSystem.h"
//I think I need text and font here too . . . . Maybe(?)
#include "Renderer/Model.h"
//#include "Renderer/Color.h"
//input
#include "Input/Input.h"
//audio
#include "Audio/Audio.h"

// ** math **
#include "Math/Vector2.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"
#include "Math/Rect.h"

// ** framework **
#include "Framework/Actor.h"
#include "Framework/Scene.h"

// ** Resources **
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"

// ** Events **
#include "Event/EventSystem.h"

// ** Components **
#include "Components/TextureComponent.h" //texture component includes rendercomponent and component so it's three for one
#include "Components/EnginePhysicsComponent.h"
#include "Components/TextComponent.h"

//** Physics **
#include "Physics/Physics.h"

#include <SDL.h>
#include <fmod.hpp>
#include <memory>
#include <cassert>


class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }
	Time& GetTime() { return *m_time; }
	ParticleSystem& GetPS() { return *m_particleSystem; }
	Physics& GetPhysics() { return *m_physics; }

	bool IsQuit() { return quit; }

private:
	bool quit{ false };

	std::unique_ptr<Renderer> m_renderer; //shared pointer
	std::unique_ptr<Input> m_input;
	std::unique_ptr<Audio> m_audio;
	std::unique_ptr<Time> m_time;
	std::unique_ptr<Physics> m_physics;

	std::unique_ptr<ParticleSystem> m_particleSystem;
};


//extern Engine g_engine; extern states that this is not the definition


//framework   actor

//renderer   particles particles systems

//math  vector2, (mathutils?)

//engine and enginecpp stay in the root folder