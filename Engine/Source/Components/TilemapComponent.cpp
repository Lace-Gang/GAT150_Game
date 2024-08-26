#include "TilemapComponent.h"

#include "Framework/Actor.h"
#include "Framework/Scene.h"


FACTORY_REGISTER(TilemapComponent);

void TilemapComponent::Initialize()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		int tileIndex = tiles[i];
		if (tileIndex == 0) continue;

		std::string tileName = tileNames[tileIndex]; 
		auto tile = Factory::Instance().Create<Actor>(tileName);
		if (tile) //does have an overload so it will automatically return if it's empty or not. So no need to state "if tile not null"
		{
			int x = i % numColumns;
			int y = i / numColumns; //columns, NOT rows (this gives us which row though)

			tile->transform.position = owner->transform.position + Vector2{ x, y } * tileSize;
			owner->scene->AddActor(std::move(tile), true);
		}
	}
}

void TilemapComponent::Update(float dt)
{
	//
}

void TilemapComponent::Read(const json_t& value)
{
	READ_DATA(value, numColumns);
	READ_DATA(value, numRows);
	READ_DATA(value, tileSize);
	READ_DATA(value, tileNames);
	READ_DATA(value, tiles);
}

void TilemapComponent::Write(json_t& value)
{
	//
}