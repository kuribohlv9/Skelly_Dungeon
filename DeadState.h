#pragma once
#include "State.h"
#include "SpriteAnimation.h"

class DeadState : public State
{
public:
	DeadState(System& systems);
	~DeadState();

	bool Update(float deltatime);
	void Draw();
	State* NextState();

private:

	System m_systems;
	std::vector<SpriteAnimation*> m_animsprite;
};

