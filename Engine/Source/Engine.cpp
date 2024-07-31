#include "Engine.h"
#include <crtdbg.h> //"C runntime debugger"


bool Engine::Initialize()
{
    //tracking memory (set up)
    //enable memory leak check
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //the | is passing two perameters as one perameter (I would like to investigae how this works further) 
    //The | is a single or which means a bitwise or
    //This is using bit flags again like with the mouse clicking

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

    //display memory leaks
    _CrtMemDumpAllObjectsSince(NULL);
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
