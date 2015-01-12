// GameState.h

#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

#include "State.h"

class Entity;
class RoomManager;
class Room;
class SoundClip;

class GameState : public State
{
public:
	GameState(System& system);
	~GameState();

	bool Update(float deltatime);
	void Draw();
	State* NextState();
	void NextRoom(std::string name);
	void DrawGUI();
	void DrawBackground(int BGoffsetX, int BGoffsetY);
	SoundClip* GetSoundClip(std::string name);

private:
	void CollisionChecking();

private:
	System m_systems;
	std::vector<Entity*> m_entities;
	std::vector<SpriteAnimation*> m_GUIVector;
	std::map<std::string, SoundClip*> m_sounds;

	bool m_active;
	RoomManager* m_roomManager;
	Room* m_room;

};

#endif // GAMESTATE_H_INCLUDED
