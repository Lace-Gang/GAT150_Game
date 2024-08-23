#include "AudioSource.h"
#include "Audio.h"

#include<iostream>
#include <fmod_errors.h>

bool AudioSource::Play(Audio& audio, bool loop, float volume, float pitch)
{
	m_audioClip->m_sound->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);

	//<get audio clip m_sound>
	FMOD_RESULT result = audio.m_audio->playSound(m_audioClip->m_sound, 0, false, &m_channel);
	if (result != FMOD_OK)
	{
		std::cerr << "Error playing sound: " << FMOD_ErrorString(result);
		return false;
	}

	SetVolume(volume);
	SetPitch(pitch);

	//<call set volume method>
	//<call set pitch method>

		return true;
}

void AudioSource::Stop()
{
	if (IsPlaying()) m_channel->stop();
		//< call stop() on m_channel >
}

void AudioSource::Pause(bool pause)
{
	FMOD_RESULT result = m_channel->setPaused(pause);
		//<call setPaused() on m_channel, pass in pause>
		if (result != FMOD_OK)
		{
			std::cerr << "Error pausing sound: " << FMOD_ErrorString(result);
		}
}

bool AudioSource::IsPlaying()
{
	bool isPlaying;
	FMOD_RESULT result = m_channel->isPlaying(&isPlaying);
		//<call isPlaying() on m_channel, pass address of bool isPlaying>
		if (result != FMOD_OK)
		{
			std::cerr << "Error is playing sound: " << FMOD_ErrorString(result);
		}

	return isPlaying;
}

bool AudioSource::SetVolume(float volume)
{
	FMOD_RESULT result = m_channel->setVolume(volume);
		//<call setVolume() on m_channel, pass in the volume>
		if (result != FMOD_OK)
		{
			std::cerr << "Error setting volume: " << FMOD_ErrorString(result);
			return false;
		}

	return true;
}

bool AudioSource::SetPitch(float pitch)
{
	FMOD_RESULT result = m_channel->setPitch(pitch);
		//<call setPitch() on m_channel, pass in the volume>
		if (result != FMOD_OK)
		{
			std::cerr << "Error setting pitch: " << FMOD_ErrorString(result);
			return false;
		}

	return true;
}
