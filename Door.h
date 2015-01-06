#pragma once

class Collider;

class Door
{
public:
	Door(float x, float y, std::string roomName, std::string destinationName, float destinationX, float destinationY);
	~Door();

	Collider* GetCollider();
	std::string GetDestinationName();
	std::string GetRoomName();
	float GetDestinationX();
	float GetDestinationY();

private:
	std::string m_roomName;
	float m_x;
	float m_y;
	bool m_isVisable;

	Collider* m_collider;

	std::string m_destinationName;
	float m_destinationX;
	float m_destinationY;
};

