#pragma once
#include "Entity.h"
#include "Enemy.h"

class Player;

enum EnemyState
{
	STATE_PASSIVE,
	STATE_AGGRESSIVE,
	STATE_RETURNING
};

class Skeleton : public Enemy, public Entity
{
public:
	Skeleton(SpriteAnimation* sprite, Player* player, float startX, float startY);
	~Skeleton();

	void Update(float deltatime);
	Sprite* GetSprite();
	SpriteAnimation* GetAniSprite();
	Collider* GetCollider();
	float GetX();
	float GetY();
	void SetInvisible();																					// instantiation of the pure virtual function SetInvisible() from Enemy.h
	bool IsVisible();
	EEntityType GetType();
	void SetPosition(int x, int y);
	float GetDirectionX();
	float GetDirectionY();
	void SetOrigin(int x, int y);



private:
	float m_x;
	float m_y;
	float m_directionX;
	float m_directionY;
	float m_originPositionX;
	float m_originPositionY;
	float m_speed;
	float m_attackTimer;
	bool m_visible;

	EnemyState m_state;
	Player* m_player;

	Collider* m_collider;
	SpriteAnimation* m_sprite;
};

