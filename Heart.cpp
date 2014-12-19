// Heart.cpp

#include "stdafx.h"
#include "Heart.h"
#include "Item.h"																					// do I need this?
#include "Collider.h"
#include "Sprite.h"


Heart::Heart(Sprite* sprite, float startX, float startY)
{
	m_sprite = sprite;
	
	m_x = startX;
	m_y = startY;

	//Initialize Collider
	m_collider = new Collider(m_x, m_y);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w, m_sprite->GetRegion()->h);

	m_visible = true;
}


Heart::~Heart()
{
	if (m_collider)
	{
		delete m_collider;
		m_collider = nullptr;
	}
}


void Heart::Update(float deltatime)
{
}

Sprite* Heart::GetSprite()
{
	return m_sprite;
}

Collider* Heart::GetCollider()
{

	return m_collider;
}

float Heart::GetX()
{
	return m_x;
}

float Heart::GetY()
{
	return m_y;
}

bool Heart::IsVisible()
{

	return m_visible;

}

void Heart::SetInvisible()
{
	m_visible = false;
}

EEntityType Heart::GetType()
{
	return ENTITY_ITEM;
}

void Heart::PickUp(Player* player)
{
	// here will be the code to pick up hearts. The heart will turn invisible, we'll ignore collision for it, and Link's heart counter, a variable within Player.h, will increase
	SetInvisible();
	player->SetHearts(1);
}