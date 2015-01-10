#include "stdafx.h"
#include "SoundClip.h"

SoundClip::SoundClip()
{
	m_pxClip = nullptr;
	m_iChannel = -1;
}

SoundClip::~SoundClip()
{
	m_pxClip = nullptr;
}

SoundClip::SoundClip(Mix_Chunk* p_pxClip)
{
	m_pxClip = p_pxClip;
	m_iChannel = -1;
}

void SoundClip::Play()
{
	m_iChannel = Mix_PlayChannel(-1, m_pxClip, 0);
}

void SoundClip::Stop()
{
	if (m_iChannel == -1)
		return;

	Mix_HaltChannel(m_iChannel);
	m_iChannel = -1;
}

void SoundClip::Volume(int p_iVolume)
{
	if (m_iChannel == -1)
		return;

	Mix_Volume(m_iChannel, p_iVolume);
}

void SoundClip::Pause()
{
	if (m_iChannel == -1)
		return;

	if (Mix_Paused(m_iChannel))
	{
		Mix_Resume(m_iChannel);
	}
	else
	{
		Mix_Pause(m_iChannel);
	}
}