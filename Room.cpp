#include "stdafx.h"
#include "Room.h"
#include "Wall.h"
#include "Collider.h"
#include "Sprite.h"


Room::Room(int width, int height, TileMapVector tileMap)
{
	m_width = width;
	m_height = height;
	m_tilemap = tileMap;
}

Room::~Room()
{
}

void Room::Load(std::vector<Entity*>& entities, Sprite* sprite, int scale)
{
	for (int i = 0; i < m_height; i++)
	{
		for (int j = 0; j < m_width; j++)
		{
			if (m_tilemap[i][j] == TILE_WALL)
			{
				Wall* wall = new Wall(sprite, j * 16 * scale, i * 16 * scale);
				wall->GetCollider()->SetWidthHeight(wall->GetSprite()->GetRegion()->w * scale, wall->GetSprite()->GetRegion()->h * scale);
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