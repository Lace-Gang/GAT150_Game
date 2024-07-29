#include "Engine.h"

Engine g_engine;
//Engine Engine::ms_engine; (to do a static member variable of the class) (must be declared in the header too. kinda a lot of trouble though

bool Engine::Initialize()
{
    m_renderer = std::make_unique<Renderer>();
    m_input = std::make_unique<Input>();
    m_audio = std::make_unique<Audio>();
    m_particleSystem = std::make_unique<ParticleSystem>(1000);

    
    m_renderer->Initialize(); //the shorthand
    m_renderer->CreateWindow("Game Engine", 1200, 800);

    m_input->Initialize();
    m_audio->Initialize();
    m_time = std::make_unique <Time>();

    return true;
}

void Engine::Shutdown()
{
    m_renderer->Shutdown();
    m_input->Shutdown();
    m_audio->Shutdown();
}

void Engine::Update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {

         if (event.type == SDL_QUIT)
         {
             quit = true;
         }
         if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
         {

             quit = true;
         }

    }

    m_time->Tick();

    m_input->Update();
    m_input->Update();
    m_particleSystem->Update(m_time->GetDeltaTime());
}
