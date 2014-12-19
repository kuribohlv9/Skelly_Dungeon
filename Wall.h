#pragma once

#include "Entity.h"

class Sprite;
class Collider;

class Wall : public Entity
{
public:
	Wall(Sprite* sprite);
	~Wall();

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
	Sprite* m_sprite;
	Collider* m_collider;
};

