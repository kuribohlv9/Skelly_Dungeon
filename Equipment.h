// Equipment.h

#include "Item.h"
#include "Entity.h"

#pragma once
class Equipment :public Item, public Entity
{
public:
	Equipment();
	~Equipment();
};

