#include "AudioClip.h"

#include<iostream>


AudioClip::~AudioClip()
{
	if (!(m_sound = nullptr))
	{
		m_sound->release();
	}
	//<m_sound is not null, release the sound>
}

bool AudioClip::Create(std::string name, ...)
{
	va_list args;
	va_start(args, name);
	Audio& audio = va_arg(args, Audio);
	//<get the Audio using va_args, look at Texture.cpp as an example>
	va_end(args);

	return Load(name, audio);
}

bool AudioClip::Load(const std::string& filename, Audio& audio)
{
	//audio.m_audio->createSound(filename.c_str(), FMOD_DEFAULT, 0, &m_sound);
	audio.m_audio->createSound(filename.c_str(), FMOD_DEFAULT, 0, &m_sound);
	//<get the c string of the filename>
	//<m_sound is a nullptr>
	if (m_sound == nullptr)
	{
		std::cerr << "Could not load sound: " << filename << std::endl;
		return false;
	}

	return true;
}
