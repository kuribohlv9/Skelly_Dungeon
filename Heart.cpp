#include "stdafx.h"
#include "Heart.h"
#include "Collider.h"
#include "Sprite.h"


Heart::Heart(Sprite* sprite, float startX, float startY)
{
	m_sprite = sprite;
	
	m_x = startX;
	m_y = startY;

	m_visible = true;
}


Heart::~Heart()
{
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

EEntityType Heart::GetType()
{
	return ENTITY_HEART;
}
