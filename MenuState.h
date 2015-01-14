#pragma once
#include "State.h"
#include "SpriteText.h"
#include "Sprite.h"
#include "SpriteAnimation.h"

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
	std::vector<SpriteText*> m_spriteText;
	std::vector<Sprite*> m_sprite;
	std::vector<SpriteAnimation*> m_animsprite;
};

