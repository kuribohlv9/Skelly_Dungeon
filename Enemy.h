// Abstract class Enemy.h
#include "Entity.h"
#pragma once


class Enemy
{
public:
	virtual ~Enemy() = default;
	virtual void SetInvisible() = 0;
};
