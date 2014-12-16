// Heart.h

#pragma once

#include "Entity.h"
#include "Player.h"
#include "Item.h"


class Heart : public Item, public Entity															// inherits from both pure virtual classes, Item and Entity
{
public:
	Heart(Sprite* sprite, float startX, float startY);
	~Heart();

	void Update(float deltatime);
	Sprite* GetSprite();
	float GetX();
	float GetY();
	void SetInvisible();
	bool IsVisible();

	Collider* GetCollider();
	EEntityType GetType();
	void PickUp();																					// instantiation of the pure virtual function PickUp() from Item.h

private:
	float m_x;
	float m_y;
	bool m_visible;


	Collider* m_collider;
	Sprite* m_sprite;
};

