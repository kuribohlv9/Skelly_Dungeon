#include "stdafx.h"
#include "RoomManager.h"
#include "SpriteManager.h"
#include "Room.h"
#include "Door.h"
#include "Collider.h"


RoomManager::RoomManager()
{

}


RoomManager::~RoomManager()
{
	auto itr = m_rooms.begin();

	while (itr != m_rooms.end())
	{
		delete itr->second;
		itr->second = nullptr;
		itr++;
	}
}

Room* RoomManager::CreateRoom(std::string filename)
{
	//This function takes a filename, looks for the corresponding textfile and loads every room in that text file

	//First we open the stream
	std::ifstream stream;
	stream.open(filename.c_str());
	if (!stream.is_open())
	{
		return nullptr;
	}

	//The first line is the name of the texture we're using for the tiles
	std::string roomFilename;
	std::getline(stream, roomFilename);

	//Then, for as long as we still have rooms to load
	while (!stream.eof())
	{
		//Inside this loop we create the rooms

		//The first thing we take in is the name of the room
		std::string name;
		stream >> name;

		//If we can't find the room in our list
		auto itr = m_rooms.find(name);
		if (itr == m_rooms.end())
		{
			//Then we load the dimensions of the room
			int width, height;
			stream >> width;
			stream >> height;

			//A tilemapvector is a two dimensional vector with enums corresponding to the tiles position
			TileMapVector tileMapVector;
			char chiffer;

			//The doors in our room needs to have some special properties so we need to assign them here so we can give them to their respective doors later
			int DoorNumber;
			stream >> DoorNumber;
			std::vector<std::string> destinationName;
			std::vector<int> destinationX;
			std::vector<int> destinationY;

			for (int i = 0; i < DoorNumber; i++)
			{
				//Name of the room which the door leads to
				std::string desName;
				stream >> desName;

				//The destination the player will arrive when he enters the next room
				destinationName.push_back(desName);
				int destination;
				stream >> destination;
				destinationX.push_back(destination);
				stream >> destination;
				destinationY.push_back(destination);
			}

			//Then we need to rember which doors is which
			DoorNumber = 0;
			std::vector<Door*> doorVector;

			std::vector<Collider*>* colliderVector = new std::vector<Collider*>;

			for (int i = 0; i < height; i++)
			{
				//First we create a vector
				std::vector<tileMap> temp;
				for (int j = 0; j < width; j++)
				{
					//Then we read and check the letter and add the corresponding enum in the vector
					stream >> chiffer;
					if (chiffer == 'w')
					{
						temp.push_back(TILE_WALL);
						Collider* col = new Collider(j * 16 * 5, i * 16 * 5);
						col->SetWidthHeight(16, 16);
						colliderVector->push_back(col);
					}
					else if (chiffer == 'g')
					{
						temp.push_back(TILE_GROUND);
					}
					else if (chiffer == 'd')
					{
						temp.push_back(TILE_DOOR);

						//The doors are created based on the information we assigned above
						Door* door = new Door(j * 80, i * 80, name, destinationName[DoorNumber], destinationX[DoorNumber], destinationY[DoorNumber]);
						doorVector.push_back(door);
						DoorNumber++;
					}
					else if (chiffer == 'e')
					{
						temp.push_back(TILE_ENEMY);
					}
					else
					{
						temp.push_back(TILE_UNKNOWN);
					}
				}
				//At the end we push back the vector into our tilemapvector, making the two dimensional vector
				tileMapVector.push_back(temp);
			}
			//The room is then created and assigned with all the neccessary information
			Room* room = new Room(name, width, height, tileMapVector, doorVector, DoorNumber, colliderVector);

			//m_rooms keeps a track of every room created and their names, this way it can be deleted and fetched with ease
			m_rooms.insert(std::pair<std::string, Room*>(name, room));

		}
	}
	//We always send back room1 because it is the first room the player should start in
	auto itr = m_rooms.find("room1");
	stream.close();
	return itr->second;
}

void RoomManager::AddSprite(std::string name, SpriteAnimation* sprite)
{
	//Roommanager also has a sprite vector, but it doesn't need deleting since they are destroyed in spritemanager
	auto itr = m_sprites.find(name);
	if (itr == m_sprites.end())
	{
		m_sprites.insert(std::pair<std::string, SpriteAnimation*>(name, sprite));
		itr = m_sprites.find(name);
	}
}

SpriteAnimation* RoomManager::GetSprite(std::string name)
{
	auto itr = m_sprites.find(name);
	return itr->second;
}
Room* RoomManager::GetRoom(std::string name)
{
	auto itr = m_rooms.find(name);
	return itr->second;
}