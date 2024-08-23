#pragma once
#include "Resources/Resource.h"
#include"Audio/Audio.h"

#include<fmod.hpp>

class AudioClip : public Resource
{
public:
	AudioClip() = default;
	~AudioClip();

	bool Create(std::string name, ...) override;
	bool Load(const std::string& filename, class Audio& audio);

	friend class Audio;
	friend class AudioSource;
	//<allow the Audio and AudioSource class access to the m_sound data, remember friend ? >

private:
	FMOD::Sound * m_sound{ nullptr };
};
