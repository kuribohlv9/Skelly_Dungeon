#pragma once

class Room;
class SpriteManager;
class Sprite;

class RoomManager
{
public:
	RoomManager(SpriteManager* spriteManager);
	~RoomManager();

	Room* CreateRoom(std::string filename);
	void AddSprite(std::string name, Sprite* sprite);
	Sprite* GetSprite(std::string name);

private:

	std::map<std::string, Room*> m_rooms;
	std::map<std::string, Sprite*> m_sprites;
	SpriteManager* m_spriteManager;
};

