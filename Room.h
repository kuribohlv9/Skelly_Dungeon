#pragma once

enum tileMap
{
	TILE_WALL,
	TILE_GROUND,
	TILE_UNKNOWN
};

typedef std::vector<std::vector<tileMap>> TileMapVector;

class Entity;
class Sprite;

class Room
{
public:
	Room(int width, int height, TileMapVector tileMap);
	~Room();

	void Load(std::vector<Entity*>& entities, Sprite* sprite, int scale);

	TileMapVector GetTilemap();
	int GetWidth();
	int GetHeight();

private:
	int m_width;
	int m_height;
	TileMapVector m_tilemap;

};

