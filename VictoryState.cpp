#include "stdafx.h"
#include "VictoryState.h"
#include "GameState.h"
#include "Keyboard.h"
#include "InputManager.h"
#include "DrawManager.h"
#include "SpriteManager.h"


VictoryState::VictoryState(System& systems)
{
	m_systems = systems;
	SDL_SetRenderDrawColor(m_systems.draw_manager->GetRenderer(), 0, 255, 0, 255);

	//Creates victory prompt sprites
	SpriteAnimation* sprite = m_systems.sprite_manager->CreateAnimatedSprite("../Skelly_Dungeon/assets/victory.txt");
	sprite->SetAnimation("victory");
	m_animsprite.push_back(sprite);

	sprite->SetAnimation("elipses");
	m_animsprite.push_back(sprite);

	sprite->SetAnimation("fornow");
	m_animsprite.push_back(sprite);

}


VictoryState::~VictoryState()
{
}

bool VictoryState::Update(float deltatime)
{
	if (m_systems.input_manager->GetKeyboard()->IsKeyDown(0) == true)
	{
		return false;
	}
	return true;
}

void VictoryState::Draw()
{
	//Draws victory prompt sprites
	m_systems.draw_manager->Draw(m_animsprite[0], 10, 10, 1);
	m_systems.draw_manager->Draw(m_animsprite[1], 454, 180, 1);
	m_systems.draw_manager->Draw(m_animsprite[2], 387, 355, 1);
}

State* VictoryState::NextState()
{
	return new GameState(m_systems);
}