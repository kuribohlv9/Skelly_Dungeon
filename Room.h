#pragma once

enum tileMap
{
	TILE_WALL,
	TILE_GROUND,
	TILE_DOOR,
	TILE_ENEMY,
	TILE_UNKNOWN
};

typedef std::vector<std::vector<tileMap>> TileMapVector;

class Collider;
class Door;
class Entity;
class SpriteAnimation;

class Room
{
public:
	Room(std::string name, int width, int height, TileMapVector tileMap, std::vector<Door*> doorVector, int doorNumber, std::vector<Collider*>* wallColliders);
	~Room();

	std::vector<Entity*> Load(int scale, SpriteAnimation* skeletonSprite);

	TileMapVector GetTilemap();
	int GetWidth();
	int GetHeight();
	std::vector<Collider*>* GetCollider();
	std::string GetName();
	Door* GetDoor(int number);
	int GetDoorNumber();

private:
	std::string m_name;
	int m_width;
	int m_height;
	TileMapVector m_tilemap;
	std::vector<Collider*>* m_wall_colliders;
	std::vector<Door*> m_doors;
	int m_doorNumber;
};

