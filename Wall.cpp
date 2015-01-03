#include "stdafx.h"
#include "Wall.h"
#include "Collider.h"
#include "Sprite.h"


Wall::Wall(Sprite* sprite, float x, float y)
{
	m_x = x;
	m_y = y;
	m_collider = new Collider(m_x, m_y);

	m_sprite = sprite;
	m_visible = true;
}


Wall::~Wall()
{
	if (m_collider)
	{
		delete m_collider;
		m_collider = nullptr;
	}
}
void Wall::Update(float deltatime)
{

}
Sprite* Wall::GetSprite()
{
	return m_sprite;
}
Collider* Wall::GetCollider()
{
	return m_collider;
}
float Wall::GetX()
{
	return m_x;
}
float Wall::GetY()
{
	return m_y;
}
bool Wall::IsVisible()
{
	return m_visible;
}
EEntityType Wall::GetType()
{
	return ENTITY_WALL;
}