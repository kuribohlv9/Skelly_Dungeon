#pragma once
#include "State.h"
class VictoryState : public State
{
public:
	VictoryState(System &systems);
	~VictoryState();

	bool Update(float deltatime);
	void Draw();
	State* NextState();

private:

	System m_systems;
};

