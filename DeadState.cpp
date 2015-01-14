#include "stdafx.h"
#include "DeadState.h"
#include "InputManager.h"
#include "Keyboard.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "SpriteAnimation.h"


DeadState::DeadState(System& systems)
{
	m_systems = systems;
	SDL_SetRenderDrawColor(m_systems.draw_manager->GetRenderer(), 255, 0, 0, 255);
	SpriteAnimation* sprite = m_systems.sprite_manager->CreateAnimatedSprite("../Skelly_Dungeon/assets/youdied.txt");
	sprite->SetAnimation("youdied");
	m_animsprite.push_back(sprite);
}


DeadState::~DeadState()
{
}

bool DeadState::Update(float deltatime)
{
	if (m_systems.input_manager->GetKeyboard()->IsKeyDown(5) == true)
	{
		return false;
	}
	return true;
}

void DeadState::Draw()
{
	m_systems.draw_manager->Draw(m_animsprite[0], 280, 380, 1);
}

State* DeadState::NextState()
{
	return nullptr;
}