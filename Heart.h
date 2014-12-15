#include "Entity.h"
#include "Player.h"

#pragma once

class Heart : public Entity
{
public:
	Heart(Sprite* sprite, float startX, float startY);
	~Heart();

	void Update(float deltatime);
	Sprite* GetSprite();
	Collider* GetCollider();
	float GetX();
	float GetY();
	bool IsVisible();
	EEntityType GetType();

private:
	float m_x;
	float m_y;
	bool m_visible;


	Collider* m_collider;
	Sprite* m_sprite;
};

