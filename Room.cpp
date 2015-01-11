#include "stdafx.h"
#include "Room.h"
#include "Wall.h"
#include "Collider.h"
#include "Sprite.h"


Room::Room(std::string name, int width, int height, TileMapVector tileMap, std::vector<Door*> doorVector, int doorNumber)
{
	m_name = name;
	m_width = width;
	m_height = height;
	m_tilemap = tileMap;
	m_doorNumber = doorNumber;

	m_doors = doorVector;
}

Room::~Room()
{
}

void Room::Load(int scale)
{
	//As long as the room is not loaded the walls doesn't have colliders. This was an attempt at optimization which might be uneccessary
	//When rooms are switched in gamestate, the colliders are deleted
	m_wall_colliders = new std::vector < Collider* > ;
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			if (m_tilemap[i][j] == TILE_WALL)
			{
				Collider* col = new Collider(j * 16 * scale, i * 16 * scale);
				col->SetWidthHeight(16, 16);
				m_wall_colliders->push_back(col);
			}
		}
	}

	//WARNING WARNING
	//Discovered that walls colliders are NOT DELETED wtf. This need fixing in some way. Optimization fail
	//WARNING WARNING
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