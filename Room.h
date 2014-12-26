#pragma once

enum tileMap
{
	TILE_WALL,
	TILE_GROUND,
	TILE_UNKNOWN
};

typedef std::vector<std::vector<tileMap>> TileMapVector;

class Room
{
public:
	Room(int width, int height);
	~Room();

	TileMapVector* GetTilemap();

private:
	int m_width;
	int m_height;
	TileMapVector m_tilemap;

};

