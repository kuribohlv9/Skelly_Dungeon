#include "stdafx.h"
#include "RoomManager.h"
#include "SpriteManager.h"
#include "Room.h"


RoomManager::RoomManager(SpriteManager* spriteManager)
{
	m_spriteManager = spriteManager;
}


RoomManager::~RoomManager()
{
}

Room* RoomManager::CreateRoom(std::string filename)
{
	std::ifstream stream;
	stream.open(filename.c_str());
	if (!stream.is_open())
	{
		return nullptr;
	}
	std::string roomFilename;
	std::getline(stream, roomFilename);

	std::string name;

	stream >> name;

	auto itr = m_rooms.find(name);
	if (itr == m_rooms.end())
	{

		int width, height;
		stream >> width;
		stream >> height;

		//				!!WARNING IMPORTANT IMPORTANT!!
		//		This vector needs to be deleted or turned into a pointer and then deleted at room destructor or i need to figure out something
		//				!!WARNING IMPORTANT IMPORTANT!!
		TileMapVector tileMapVector;

		char chiffer;

		for (int i = 0; i < height; i++)
		{
			std::vector<tileMap> temp;
			for (int j = 0; j < width; j++)
			{
				stream >> chiffer;
				if (chiffer == 'w')
				{
					temp.push_back(TILE_WALL);
				}
				else if (chiffer == 'g')
				{
					temp.push_back(TILE_GROUND);
				}
				else
				{
					temp.push_back(TILE_UNKNOWN);
				}
			}

			tileMapVector.push_back(temp);
		}

		Room* room = new Room(width, height, tileMapVector);

		m_rooms.insert(std::pair<std::string, Room*>(name, room));
		itr = m_rooms.find(name);

	}
	stream.close();
	return itr->second;
}

void RoomManager::AddSprite(std::string name, Sprite* sprite)
{
	auto itr = m_sprites.find(name);
	if (itr == m_sprites.end())
	{
		m_sprites.insert(std::pair<std::string, Sprite*>(name, sprite));
		itr = m_sprites.find(name);
	}
}

Sprite* RoomManager::GetSprite(std::string name)
{
	auto itr = m_sprites.find(name);
	return itr->second;
}