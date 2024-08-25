#include "Engine.h"
#include "SpaceGame.h"
#include "SquirrelGame.h"
//#include "Components/PlayerComponent.h"

#include "Framework/Scene.h"
#include "Framework/Actor.h"

#include "Renderer/Texture.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include<cassert> //modern. the older one was assert.h but c++ is moving away from having .h in includes
//#include <Renderer/Text.h>





int main(int argc, char* argv[])

{	
	//build is the working deirectory (where we "start" when the program runs.) Below we move to the assets folder
	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	

	//gonna get rid of our global variables as they are typically frowned upon
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();
	

	std::unique_ptr<SquirrelGame> game = std::make_unique<SquirrelGame>(engine.get());
//	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>(engine.get());
	game->Initialize();

	{

		while (!engine->IsQuit())
		{

			//____INPUT/UPDATE____

			engine->Update();
			game->Update(engine->GetTime().GetDeltaTime());

			
			//____DRAW____

			//	// clear screen
			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			game->Draw(engine->GetRenderer());


			engine->GetRenderer().EndFrame();
		}
	}

	//shut everything down
	game->Shutdown();
	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}
