// MusicClip.cpp
#include "stdafx.h" 
#include "MusicClip.h"
 
MusicClip::MusicClip()
{
    m_xClip = nullptr;
    m_iChannel = -1;
}
 
MusicClip::~MusicClip()
{
	m_xClip = nullptr;
	m_iChannel = -1;
}
 
MusicClip::MusicClip(Mix_Music* p_xClip)
{
	m_xClip = p_xClip;
	m_iChannel = -1;
}
 
void MusicClip::Play()
{
	m_iChannel = Mix_PlayMusic(m_xClip, -1);
}
 
void MusicClip::Pause()
{
	if (m_iChannel == -1)
        return;
 
    if ( Mix_PausedMusic() )
		Mix_ResumeMusic();
    else
		Mix_Pause(m_iChannel);
}
 
void MusicClip::Volume(int p_iVolume)
{
	Mix_VolumeMusic(p_iVolume);
}
 
void MusicClip::Stop()
{
	if (m_iChannel == -1)
             return;
 
	Mix_HaltChannel(m_iChannel);
	m_iChannel = -1;
}