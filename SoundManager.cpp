#include "stdafx.h"
#include "SoundManager.h"
#include "MusicClip.h"
#include "SoundClip.h"

SoundManager::SoundManager()
{
	
}

SoundManager::~SoundManager()
{
	Shutdown();
}

bool SoundManager::Initialize()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf(" SDL_mixer :: Msx_OpenAudio %s\n", Mix_GetError());
		return false;
	}
	return true;
}

void SoundManager::Shutdown()
{
	for (unsigned int i = 0; i < m_axSoundClips.size(); i++)
	{
		delete m_axSoundClips[i];
		m_axSoundClips[i] = nullptr;
	}
	m_axSoundClips.clear();

	for (unsigned int i = 0; i < m_axMusicClips.size(); i++)
	{
		delete m_axMusicClips[i];
		m_axMusicClips[i] = nullptr;
	}
	m_axMusicClips.clear();

	{
		std::map<std::string, Mix_Chunk*>::iterator it = m_axSounds.begin();
		while (it != m_axSounds.end())
		{
			Mix_FreeChunk(it->second);
			it->second = nullptr;
			it++;
		}
		m_axSounds.clear();
	}

	{
		std::map<std::string, Mix_Music*>::iterator it = m_axMusic.begin();
		while (it != m_axMusic.end())
		{
			Mix_FreeMusic(it->second);
			it->second = nullptr;
			it++;
		}
		m_axMusic.clear();
	}

	Mix_CloseAudio();
}

MusicClip *SoundManager::CreateMusicClip(std::string p_sFilename)
{
	MusicClip *Ret = nullptr;

	std::map<std::string, Mix_Music*>::iterator it = m_axMusic.find(p_sFilename);

	if (it == m_axMusic.end())
	{
		Mix_Music *Music = Mix_LoadMUS(p_sFilename.c_str());
		std::pair<std::string, Mix_Music*> Pair;
		Pair = std::make_pair(p_sFilename, Music);
		m_axMusic.insert(Pair);
		Ret = new MusicClip(Music);
	}
	else
		Ret = new MusicClip(it->second);

	m_axMusicClips.push_back(Ret);

	return Ret;
}

SoundClip *SoundManager::CreateSoundClip(std::string p_sFilename)
{
	SoundClip *Ret = nullptr;

	std::map<std::string, Mix_Chunk*>::iterator it = m_axSounds.find(p_sFilename);

	if (it == m_axSounds.end())
	{
		Mix_Chunk *Sound = Mix_LoadWAV(p_sFilename.c_str());
		std::string derp = SDL_GetError();
		m_axSounds.insert(std::pair<std::string, Mix_Chunk*>(p_sFilename, Sound));
		Ret = new SoundClip(Sound);
	}
	else
		Ret = new SoundClip(it->second);

	m_axSoundClips.push_back(Ret);

	return Ret;
}