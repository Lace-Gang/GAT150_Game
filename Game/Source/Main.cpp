#include "Engine.h"
#include "Components/PlayerComponent.h"

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

	
	//Factory::Instance().Register<Actor>(Actor::GetTypeName());
	//Factory::Instance().Register<TextureComponent>(TextureComponent::GetTypeName());
	//Factory::Instance().Register<EnginePhysicsComponent>(EnginePhysicsComponent::GetTypeName());
	//Factory::Instance().Register<PlayerComponent>(PlayerComponent::GetTypeName());
	//Factory::Instance().Register<TextComponent>(TextComponent::GetTypeName());

	//auto a = Factory::Instance().Create<Actor>("Actor");



	//gonna get rid of our global variables as they are typically frowned upon
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();


	//build is the working deirectory (where we "start" when the program runs.) Below we move to the assets folder
	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;


	//testing the file reading
	//std::string buffer;
	//File::ReadFile("Scenes/scene.json", buffer);
	//std::cout << buffer << std::endl;
	

	rapidjson::Document document;
	Json::Load("Scenes/scene.json", document);
	
	std::unique_ptr<Scene> scene = std::make_unique<Scene>(engine.get());
	scene->Read(document);
	scene->Initialize();


	{

		//// create texture, using shared_ptr so texture can be shared
		//res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("Textures/changeMyMindMeme.jpg", engine->GetRenderer()); 	//////res_t<Texture> texture2 = rm.Get<Texture>("changeMyMindMeme.jpg", engine->GetRenderer());
		////texture->Load("changeMyMindMeme.jpg", engine->GetRenderer());
		//res_t<Font> font = ResourceManager::Instance().Get<Font>("Fonts/homespun.ttf", 20);
		//Text* text = new Text(font.get());
		//text->Create(engine->GetRenderer(), "Hello!", Color{ 1, 1, 1, 1 });


		
		//auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
		//actor->transform = Transform { Vector2{ 30, 30 } };
		//auto component = Factory::Instance().Create<TextureComponent>(TextureComponent::GetTypeName());
		//component->texture = texture;
		//actor->AddComponent(std::move(component));
		//

		while (!engine->IsQuit())
		{

			//____INPUT/UPDATE____

			engine->Update();
			scene->Update(engine->GetTime().GetDeltaTime());

			auto* actor = scene->GetActor<Actor>("Text");
			if (actor)
			{
				actor->transform.scale = Math::Abs(Math::Sin(engine->GetTime().GetTime()) * 5);
				actor->transform.rotation += 90 * engine->GetTime().GetDeltaTime();
			}

			//____DRAW____

			//	// clear screen
			engine->GetRenderer().SetColor(0, 0, 0, 0);
			engine->GetRenderer().BeginFrame();

			scene->Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();
		}
	}

	scene->RemoveAll();
	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}
