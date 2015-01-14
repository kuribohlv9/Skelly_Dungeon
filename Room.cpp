#include "stdafx.h"
#include "Room.h"
#include "Wall.h"
#include "Collider.h"
#include "Skeleton.h"
#include "SpriteAnimation.h"


Room::Room(std::string name, int width, int height, TileMapVector tileMap, std::vector<Door*> doorVector, int doorNumber, std::vector<Collider*>* wallColliders)
{
	m_name = name;
	m_width = width;
	m_height = height;
	m_tilemap = tileMap;
	m_doorNumber = doorNumber;

	m_doors = doorVector;
	m_wall_colliders = wallColliders;
}

Room::~Room()
{
	auto it = m_wall_colliders->begin();

	while (it != m_wall_colliders->end())
	{
		delete *it;
		*it = nullptr;
		it++;
	}
	m_wall_colliders->clear();

	auto itr = m_doors.begin();
	while (itr != m_doors.end())
	{
		delete *itr;
		*itr = nullptr;
		itr++;
	}
}

std::vector<Entity*> Room::Load(int scale, SpriteAnimation* skeletonSprite, Player* player)
{

	std::vector<Entity*> tempVector;
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			if (m_tilemap[i][j] == TILE_ENEMY)
			{
				Skeleton* skelly = new Skeleton(skeletonSprite, player, j * 16.0f * scale, i * 16.0f * scale);
				tempVector.push_back(skelly);
			}
		}
	}
	return tempVector;
}

TileMapVector Room::GetTilemap()
{
	return m_tilemap;
}
int Room::GetWidth()
{
	return m_width;
	
}
int Room::GetHeight()
{
	return m_height;
}

std::vector<Collider*>* Room::GetCollider()
{
	return m_wall_colliders;
}

std::string Room::GetName()
{
	return m_name;
}

Door* Room::GetDoor(int number)
{
	return m_doors[number];
}
int Room::GetDoorNumber()
{
	return m_doorNumber;
}