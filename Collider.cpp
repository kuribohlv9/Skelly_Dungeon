// Collider.cpp

#include "stdafx.h"
#include "Entity.h"
#include "Collider.h"

Collider::Collider(float x, float y)
{
	m_parent = nullptr;
	m_area.x = x;
	m_area.y = y;
	m_area.w = 0;
	m_area.h = 0;
}

bool Collider::HasParent()
{
	return m_parent != nullptr;
}

void Collider::SetParent(Entity* parent)
{
	m_parent = parent;
}

Entity* Collider::GetParent()
{
	return m_parent;
}

void Collider::SetPosition(float x, float y)
{
	m_area.x = x;
	m_area.y = y;
}

void Collider::SetWidthHeight(int width, int height)
{
	m_area.w = width * 5;
	m_area.h = height * 5;
}

int Collider::GetX()
{
	return m_area.x;
}

int Collider::GetY()
{
	return m_area.y;
}

int Collider::GetWidth()
{
	return m_area.w;
}

int Collider::GetHeight()
{
	return m_area.h;
}

void Collider::Refresh()
{
	m_area.x = m_parent->GetX();
	m_area.y = m_parent->GetY();
}
