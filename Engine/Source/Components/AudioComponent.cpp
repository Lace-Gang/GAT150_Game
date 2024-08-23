#include "AudioComponent.h"

#include "Audio/AudioClip.h"
#include "Audio/AudioSource.h"
#include "Resources/ResourceManager.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Engine.h"

#include<memory>



FACTORY_REGISTER(AudioComponent)

AudioComponent::AudioComponent(const AudioComponent& other)
{
	soundName = other.soundName;
	playOnStart = other.playOnStart;
	loop = other.loop;
	volume = other.volume;
	pitch = other.pitch;
	//<copy the rest of the data from the other to this>

		if (other.m_audioSource)
		{
			m_audioSource = std::make_unique<AudioSource>(*other.m_audioSource.get());
		}
}

void AudioComponent::Initialize()
{
	if (!m_audioSource && !soundName.empty())
	{
		auto audioClip = ResourceManager::Instance().Get<AudioClip>(soundName, owner->scene->engine->GetAudio());
		m_audioSource = std::make_unique<AudioSource>(audioClip);
		//<make unique pointer, pass in audioClip to constructor>
	}
}

void AudioComponent::Update(float dt)
{
	//<check if playOnStart is true>
	if (playOnStart)
	{
		playOnStart = false;
		Play();
		//< set playOnStart to not play on next Update();
		//<call Play()>
	}
}

void AudioComponent::Play()
{
	//<get engine GetAudio()>
	if (m_audioSource) m_audioSource->Play(owner->scene->engine->GetAudio(), loop, volume, pitch);
}

void AudioComponent::Play(bool loop, float volume, float pitch)
{
	if (m_audioSource) m_audioSource->Play(owner->scene->engine->GetAudio(), loop, volume, pitch);
}

bool AudioComponent::IsPlaying()
{
	//< and the audio source is playing>
	return (m_audioSource->IsPlaying());
}

void AudioComponent::Stop()
{
	if (m_audioSource) m_audioSource->Stop();
	//< call audio source Stop() >
}

void AudioComponent::Pause(bool pause)
{
	if (m_audioSource) m_audioSource->Pause(pause);
	//< call audio source Pause() pass in pause >
}

void AudioComponent::SetVolume(float volume)
{
	if(IsPlaying()) this->volume = volume;
	//<if IsPlaying() set the volume of the audio source>
}

void AudioComponent::SetPitch(float pitch)
{
	if(IsPlaying()) this->pitch = pitch;
	//<if IsPlaying() set the pitch of the audio source>
}

void AudioComponent::Read(const json_t& value)
{
	READ_DATA(value, playOnStart);
	READ_DATA(value, loop);
	READ_DATA(value, volume);
	READ_DATA(value, pitch);
	READ_DATA(value, soundName);
	//<read in the data of the class variables>
}

void AudioComponent::Write(json_t& value)
{
	//
}
