#pragma once
#include "Entity.h"

class Keyboard;

class Player : public Entity
{
public:
	Player(Keyboard* keyboard, Sprite* sprite);
	~Player();

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
	float m_speed;
	bool m_visible;

	Collider* m_collider;
	Sprite* m_sprite;
	Keyboard* m_keyboard;
};

