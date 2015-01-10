#pragma once
#include "Entity.h"

class Keyboard;

enum PlayerState
{
	STATE_ATTACKING,
	STATE_NORMAL,
	STATE_DAMAGE
};

class Player : public Entity
{
public:
	Player(Keyboard* keyboard, SpriteAnimation* sprite);
	~Player();

	void Update(float deltatime);
	Sprite* GetSprite();
	SpriteAnimation* GetAniSprite();
	Collider* GetCollider();
	Collider* GetSwordCollider();
	float GetX();
	float GetY();
	bool IsVisible();
	EEntityType GetType();
	void SetPosition(int x, int y);
	PlayerState GetState();

	void SetHearts(int change);																		// a public function for changing the heart counter, HeartCounter, a protected variable
//	void SetSword(bool change);

private:
	float m_x;
	float m_y;
	float m_speed;
	float m_attackTimer;
	bool m_visible;
	bool m_attacking;																				// a variable to check if the player is attacking
	std::string m_direction;
	std::string m_last_direction;

	PlayerState m_state;

	float HeartCounter;																				// holds the heart counter variable. Since it's private, we need a public function for changing it, accessible from GameState.cpp
//	bool HasSword;																					// holds the HasSword variable.

	Collider* m_collider;
	SpriteAnimation* m_sprite;
	Keyboard* m_keyboard;
	Collider* m_swordCollider;
};

