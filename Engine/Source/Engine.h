#pragma once

#include "Renderer.h" 
#include "Input.h"
#include "Audio.h"

#include "Vector2.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "Model.h"

#include "Random.h"
#include "ETimer.h"
#include "Color.h"
#include "MathUtils.h"
#include "Transform.h"
#include "ETimer.h"

#include <SDL.h>
#include <fmod.hpp>
#include <memory>


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

	bool IsQuit() { return quit; }

private:
	bool quit{ false };

	std::unique_ptr<Renderer> m_renderer; //shared pointer
	std::unique_ptr<Input> m_input;
	std::unique_ptr<Audio> m_audio;
	std::unique_ptr<Time> m_time;

	std::unique_ptr<ParticleSystem> m_particleSystem;
};


extern Engine g_engine; 
