#include "stdafx.h"
#include "RoomManager.h"
#include "SpriteManager.h"
#include "Room.h"
#include "Door.h"


RoomManager::RoomManager(SpriteManager* spriteManager)
{
	m_spriteManager = spriteManager;
}


RoomManager::~RoomManager()
{
	auto itr = m_rooms.begin();

	while (itr != m_rooms.end())
	{
		delete itr->second;
	}
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

	while (!stream.eof())
	{
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


			int DoorNumber;
			stream >> DoorNumber;

			std::vector<std::string> destinationName;
			std::vector<int> destinationX;
			std::vector<int> destinationY;
			for (int i = 0; i < DoorNumber; i++)
			{
				std::string desName;
				stream >> desName;
				destinationName.push_back(desName);
				int destination;
				stream >> destination;
				destinationX.push_back(destination);
				stream >> destination;
				destinationY.push_back(destination);
			}

			DoorNumber = 0;
			std::vector<Door*> doorVector;

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
					else if (chiffer == 'd')
					{
						temp.push_back(TILE_DOOR);
						Door* door = new Door(j * 80, i * 80, name, destinationName[DoorNumber], destinationX[DoorNumber], destinationY[DoorNumber]);
						doorVector.push_back(door);
						DoorNumber++;
					}
					else
					{
						temp.push_back(TILE_UNKNOWN);
					}
				}

				tileMapVector.push_back(temp);
			}

			Room* room = new Room(name, width, height, tileMapVector, doorVector, DoorNumber);

			m_rooms.insert(std::pair<std::string, Room*>(name, room));

		}
	}
	auto itr = m_rooms.find("room1");
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
Room* RoomManager::GetRoom(std::string name)
{
	auto itr = m_rooms.find(name);
	return itr->second;
}