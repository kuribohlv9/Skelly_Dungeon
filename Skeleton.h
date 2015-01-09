#pragma once
#include "Entity.h"
#include "Enemy.h"

class Skeleton : public Enemy, public Entity
{
public:
	Skeleton(SpriteAnimation* sprite, float startX, float startY);
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



private:
	float m_x;
	float m_y;
	float m_directionX;
	float m_directionY;
	float m_speed;
	float m_attackTimer;
	bool m_visible;


	Collider* m_collider;
	SpriteAnimation* m_sprite;
};

