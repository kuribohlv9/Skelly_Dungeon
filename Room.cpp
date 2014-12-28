#include "stdafx.h"
#include "Room.h"
#include "Wall.h"


Room::Room(int width, int height, TileMapVector tileMap)
{
	m_width = width;
	m_height = height;
	m_tilemap = tileMap;
}

Room::~Room()
{
}

void Room::Load(std::vector<Entity*>& entities, Sprite* sprite)
{
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			if (m_tilemap[i][j] == TILE_WALL)
			{
				Wall* wall = new Wall(sprite, i * 16, j * 16);
				entities.push_back(wall);
			}
		}
	}
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