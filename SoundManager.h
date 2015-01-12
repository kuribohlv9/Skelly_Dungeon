#ifndef SOUNDMANAGER_H_INCLUDED
#define SOUNDMANAGER_H_INCLUDED

#pragma once

class MusicClip;
class SoundClip;

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	bool Initialize();
	void Shutdown();
	MusicClip *CreateMusicClip(std::string p_sFilename);
	SoundClip *CreateSoundClip(std::string p_sFilename);
private:
	std::map<std::string, Mix_Music*> m_axMusic;
	std::map<std::string, Mix_Chunk*> m_axSounds;
	std::vector<MusicClip*> m_axMusicClips;
	std::vector<SoundClip*> m_axSoundClips;
};

#endif // !SOUNDMANAGER_H_INCLUDED
