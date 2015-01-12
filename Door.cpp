#include "stdafx.h"
#include "Door.h"
#include "Collider.h"


Door::Door(float x, float y, std::string roomName, std::string destinationName, float destinationX, float destinationY)
{
	m_x = x;
	m_y = y;
	m_collider = new Collider(m_x, m_y);
	m_collider->SetWidthHeight(16, 16);
	m_roomName = roomName;

	m_destinationName = destinationName;
	m_destinationX = destinationX;
	m_destinationY = destinationY;

}


Door::~Door()
{
	delete m_collider;
	m_collider = nullptr;
}

Collider* Door::GetCollider()
{
	return m_collider;
}

std::string Door::GetDestinationName()
{
	return m_destinationName;
}

std::string Door::GetRoomName()
{
	return m_roomName;
}

float Door::GetDestinationX()
{
	return m_destinationX;
}

float Door::GetDestinationY()
{
	return m_destinationY;
}