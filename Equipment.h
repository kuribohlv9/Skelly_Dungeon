// Equipment.h

#include "Item.h"
#include "Entity.h"
#include "Player.h"

#pragma once
class Equipment : public Item, public Entity
{
public:
	Equipment();
	~Equipment();

	void PickUp(Player* player);
};

