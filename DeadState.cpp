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
	SDL_SetRenderDrawColor(m_systems.draw_manager->GetRenderer(), 111, 1, 1, 255);

	//Creates death prompt sprite
	SpriteAnimation* sprite = m_systems.sprite_manager->CreateAnimatedSprite("../Skelly_Dungeon/assets/youdied.txt");
	sprite->SetAnimation("youdied");
	m_animsprite.push_back(sprite);
}


DeadState::~DeadState()
{
}

bool DeadState::Update(float deltatime)
{
	//Scales the death prompt sprite with time
	m_scale += deltatime;


	//Returning false after three scales of the death msg, used in State Manager's Update() function to go to the next state, set below to nullptr
	if (m_scale > 4)

	{
		return false;
	}
	return true;
}

void DeadState::Draw()
{
	//Draws the scaling death prompt sprite
	m_systems.draw_manager->Draw(m_animsprite[0], 10, 10, m_scale);
}

State* DeadState::NextState()
{
	//The game will close after the player dies and the death message displays
	return nullptr;
}