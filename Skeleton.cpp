#include "stdafx.h"
#include "Skeleton.h"
#include "Enemy.h"
#include "Collider.h"
#include "Sprite.h"
#include "SpriteAnimation.h"


Skeleton::Skeleton(SpriteAnimation* sprite, float startX, float startY)
{
	m_sprite = sprite;

	m_x = startX;
	m_y = startY;

	//Initialize Collider
	m_collider = new Collider(m_x, m_y);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w, m_sprite->GetRegion()->h);

	m_visible = true;
}


Skeleton::~Skeleton()
{
	if (m_collider)
	{
		delete m_collider;
		m_collider = nullptr;
	}
}


void Skeleton::Update(float deltatime)
{
}

Sprite* Skeleton::GetSprite()
{
	return m_sprite;
}

Collider* Skeleton::GetCollider()
{
	return m_collider;
}

float Skeleton::GetX()
{
	return m_x;
}

float Skeleton::GetY()
{
	return m_y;
}

bool Skeleton::IsVisible()
{

	return m_visible;

}

void Skeleton::SetInvisible()
{
	m_visible = false;
}

EEntityType Skeleton::GetType()
{
	return ENTITY_ENEMY;
}