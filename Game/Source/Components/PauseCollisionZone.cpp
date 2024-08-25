#include "PauseCollisionZone.h"


void PauseCollisionZone::Initialize()
{
	//
}

void PauseCollisionZone::Update(float dt)
{
	//
}

void PauseCollisionZone::Read(const json_t& value)
{
	READ_DATA(value, uncertainty);
}

void PauseCollisionZone::Write(json_t& value)
{
	//
}