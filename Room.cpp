#include "stdafx.h"
#include "Room.h"


Room::Room(int width, int height, TileMapVector tileMap)
{
	m_width = width;
	m_height = height;
	m_tilemap = tileMap;
}

Room::~Room()
{
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