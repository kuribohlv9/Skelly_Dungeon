#pragma once
#include "State.h"
#include "SpriteAnimation.h"

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
	std::vector<SpriteAnimation*> m_animsprite;

};

