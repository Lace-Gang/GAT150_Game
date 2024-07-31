#include <iostream>


#include "Engine.h"
#include "Framework/Scene.h"
#include "Framework/Actor.h"




#include <iostream>
#include <cstdlib>
#include <vector>
#include<cassert> //modern. the older one was assert.h but c++ is moving away from having .h in includes





int main(int argc, char* argv[])
{
	//gonna get rid of our global variables as they are typically frowned upon
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	engine->Initialize();


	File::SetFilePath("..\Build\Assets");
	std::cout << File::GetFilePath() << std::endl;


	while (!engine->IsQuit())
	{

		//____INPUT____

		engine->Update();


		//____DRAW____


		//	// clear screen
		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();

		//engine->GetPS().Draw(engine->GetRenderer());

		engine->GetRenderer().EndFrame();



	}

	engine->Shutdown();

	return 0;
}
