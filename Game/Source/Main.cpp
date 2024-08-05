#include <iostream>


#include "Engine.h"
#include "Framework/Scene.h"
#include "Framework/Actor.h"

#include "Renderer/Texture.h"




#include <iostream>
#include <cstdlib>
#include <vector>
#include<cassert> //modern. the older one was assert.h but c++ is moving away from having .h in includes





int main(int argc, char* argv[])
{
	//gonna get rid of our global variables as they are typically frowned upon
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	engine->Initialize();

	//ResourceManager rm = ResourceManager();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	// create texture, using shared_ptr so texture can be shared


	res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("changeMyMindMeme.jpg", engine->GetRenderer()); 	//////res_t<Texture> texture2 = rm.Get<Texture>("changeMyMindMeme.jpg", engine->GetRenderer());


	//texture->Load("changeMyMindMeme.jpg", engine->GetRenderer());




	while (!engine->IsQuit())
	{

		//____INPUT____

		engine->Update();


		//____DRAW____


		//	// clear screen
		engine->GetRenderer().SetColor(0, 0, 0, 0);
		engine->GetRenderer().BeginFrame();

		//engine->GetPS().Draw(engine->GetRenderer());
		engine->GetRenderer().DrawTexture(texture.get(), 30, 30);

		engine->GetRenderer().EndFrame();



	}

	engine->Shutdown();

	return 0;
}
