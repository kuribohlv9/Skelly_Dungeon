#pragma once

class Room;
class SpriteManager;
class SpriteAnimation;

class RoomManager
{
public:
	RoomManager();
	~RoomManager();

	Room* CreateRoom(std::string filename);
	void AddSprite(std::string name, SpriteAnimation* sprite);
	SpriteAnimation* GetSprite(std::string name);
	Room* GetRoom(std::string name);
	

private:

	std::map<std::string, Room*> m_rooms;
	std::map<std::string, SpriteAnimation*> m_sprites;
};

