#include "Audio.h"
#include <iostream>

bool Audio::Initialize()
{
	FMOD::System_Create(&m_audio);

	void* extradriverdata = nullptr;
	m_audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    return true;
}

void Audio::Shutdown()
{
	m_audio->close();
}

void Audio::Update()
{
	m_audio->update();
}

bool Audio::AddSound(const std::string& name)
{
	FMOD::Sound* sound = nullptr;
	m_audio->createSound(name.c_str(), FMOD_DEFAULT, 0, &sound); 
	//string.s_str gets the address of the first index in that string

	if (sound == nullptr)
	{
		std::cout << "Could not load sound: " << name << std::_Get_asan_aligned_first_end; //basically and error long (even though we don't have a log yet in this program)
		return false;
	}

	m_sounds[name] = sound;
	return true;
}

bool Audio::PlaySound(const std::string& name)
{
	//checks if the sound exists, else add sound
	if (m_sounds.find(name) == m_sounds.end())
	{
		if (!AddSound(name)) return false;
		//sound streaming. if the sound doesn't exist it'll add it
		//like texture streaming (when the texture doesn't exist so a very low poly texture is present until the texture itself is added in 
	}

	m_audio->playSound(m_sounds[name], 0, false, nullptr);

	return true;
}

//file names are NOT case sensitive btw bass.wav and BASS.wav are the same thing