#include <iostream>


#include "Engine.h"
#include "Framework/Scene.h"
#include "Framework/Actor.h"

#include "Renderer/Texture.h"
#include "Renderer/Font.h"




#include <iostream>
#include <cstdlib>
#include <vector>
#include<cassert> //modern. the older one was assert.h but c++ is moving away from having .h in includes
#include <Renderer/Text.h>





int main(int argc, char* argv[])
{
	//gonna get rid of our global variables as they are typically frowned upon
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	engine->Initialize();

	//ResourceManager rm = ResourceManager();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	{

		// create texture, using shared_ptr so texture can be shared
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("changeMyMindMeme.jpg", engine->GetRenderer()); 	//////res_t<Texture> texture2 = rm.Get<Texture>("changeMyMindMeme.jpg", engine->GetRenderer());
		//texture->Load("changeMyMindMeme.jpg", engine->GetRenderer());
		res_t<Font> font = ResourceManager::Instance().Get<Font>("homespun.ttf", 20);
		Text* text = new Text(font.get());
		text->Create(engine->GetRenderer(), "Hello!", Color{ 1, 1, 1, 1 });


		Transform t{ Vector2{ 30, 30 } };
		std::unique_ptr<Actor> actor = std::make_unique<Actor>(t);
		std::unique_ptr<TextureComponent> component = std::make_unique<TextureComponent>();
		component->texture = texture;
		actor->AddComponent(std::move(component));


		while (!engine->IsQuit())
		{

			//____INPUT/UPDATE____

			engine->Update();

			actor->Update(engine->GetTime().GetDeltaTime());

			//____DRAW____

			//	// clear screen
			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			//engine->GetPS().Draw(engine->GetRenderer());
			engine->GetRenderer().DrawTexture(texture.get(), 130, 130);

			actor->Draw(engine->GetRenderer()); 
			text->Draw(engine->GetRenderer(), 540, 540);
			

			engine->GetRenderer().EndFrame();
		}
	}

	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}
