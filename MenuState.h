#pragma once
#include "State.h"

class MenuState : public State
{
public:
	MenuState(System &systems);
	~MenuState();

	bool Update(float deltatime);
	void Draw();
	State* NextState();

private:

	System m_systems;
};

