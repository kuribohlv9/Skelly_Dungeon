// Abstract class Item.h
#pragma once

class Item
{
public:
	virtual ~Item() = default;
	// a pure virtual function for picking up items. Will be instantiated in item classes
	virtual void PickUp(Player* player) = 0;																	
																												// has a Player pointer as a parameter so we can access Player's functions and thereby its datamems, specifically for adding item counters, by inputting a player object as a param in GameState
};

