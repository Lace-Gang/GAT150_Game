#include "Engine.h"
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
	Factory::Instance().Register<Actor>(Actor::GetTypeName());
	Factory::Instance().Register<TextureComponent>(TextureComponent::GetTypeName());

	//auto a = Factory::Instance().Create<Actor>("Actor");



	//gonna get rid of our global variables as they are typically frowned upon
	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	engine->Initialize();

	//ResourceManager rm = ResourceManager();

	//build is the working deirectory (where we "start" when the program runs.) Below we move to the assets folder
	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	//testing the file reading
	std::string s;
	File::ReadFile("Texts/text.txt", s);
	std::cout << s << std::endl;

	rapidjson::Document document;
	Json::Load("Texts/text.txt", document);

	std::string name;
	int age;
	bool isAwake;
	Vector2 position;
	Color color;
	float speed;

	

	////how to get specific data points from json 
	//Json::Read(document, "age", age);
	//Json::Read(document, "name", name);
	//Json::Read(document, "isDormant", isDormant);
	//Json::Read(document, "position", position);
	//Json::Read(document, "color", color);
	//
	//std::cout << age << std::endl;
	//std::cout << name << std::endl;
	//std::cout << isAwake << std::endl;
	//std::cout << "[" << position.x << ", " << position.y << "]" << std::endl;
	//std::cout << "[" << color.r << ", " << color.g << color.b << ", " << color.a << "]" << std::endl;
	//
	
	////another way to do it
	//name = "null";
	//age = 0;
	//isAwake = true;
	//position.x = 0;
	//position.y = 0;
	//color.r = 0;
	//color.g = 0;
	//color.b = 0;
	//color.a = 0.5;
	
	READ_DATA(document, isAwake);
	READ_DATA(document, name);
	READ_DATA(document, age);
	READ_DATA(document, position);
	READ_DATA(document, color);
	READ_DATA(document, speed);
	std::cout << name << " " << age << " " << speed << " " <<  isAwake << std::endl;
	std::cout << position.x << ", " << position.y << std::endl;
	std::cout << color.r << ", " << color.g << color.b << ", " << color.a << std::endl;

	{

		// create texture, using shared_ptr so texture can be shared
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("Images/changeMyMindMeme.jpg", engine->GetRenderer()); 	//////res_t<Texture> texture2 = rm.Get<Texture>("changeMyMindMeme.jpg", engine->GetRenderer());
		//texture->Load("changeMyMindMeme.jpg", engine->GetRenderer());
		res_t<Font> font = ResourceManager::Instance().Get<Font>("Fonts/homespun.ttf", 20);
		Text* text = new Text(font.get());
		text->Create(engine->GetRenderer(), "Hello!", Color{ 1, 1, 1, 1 });


		Transform t{ Vector2{ 30, 30 } };
		auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
		actor->SetTransform(t);
		auto component = Factory::Instance().Create<TextureComponent>(TextureComponent::GetTypeName());
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
