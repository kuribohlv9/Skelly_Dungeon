#pragma once

class Room;

class RoomManager
{
public:
	RoomManager();
	~RoomManager();

	void CreateRoom(std::string filename);

private:

	std::vector<Room*> m_rooms;
};

