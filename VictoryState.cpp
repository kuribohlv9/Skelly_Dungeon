#include "stdafx.h"
#include "VictoryState.h"
#include "GameState.h"
#include "Keyboard.h"
#include "InputManager.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "SpriteAnimation.h"


VictoryState::VictoryState(System& systems)
{
	m_systems = systems;
	SDL_SetRenderDrawColor(m_systems.draw_manager->GetRenderer(), 98, 98, 98, 255);

	//Creates victory prompt sprites
	SpriteAnimation* sprite = m_systems.sprite_manager->CreateAnimatedSprite("../Skelly_Dungeon/assets/victory.txt");
	sprite->SetAnimation("victory");
	m_animsprite.push_back(sprite);

	sprite = m_systems.sprite_manager->CreateAnimatedSprite("../Skelly_Dungeon/assets/fornow.txt");
	sprite->SetAnimation("fornow");
	m_animsprite.push_back(sprite);

}


VictoryState::~VictoryState()
{
}

bool VictoryState::Update(float deltatime)
{
	//Updates the animated sprites in our vector
	for (int i = 0; i < m_animsprite.size(); i++)
	{
		m_animsprite[i]->Update(deltatime);
	}

	//Returns false if the player presses enter, used in State Manager's Update() function to go to the next state, specified below as GameState 
	if (m_systems.input_manager->GetKeyboard()->IsKeyDown(5) == true)
	{
		return false;
	}
	return true;
}

void VictoryState::Draw()
{
	//Draws victory prompt sprites
	m_systems.draw_manager->Draw(m_animsprite[0], 162, 100, 1);
	m_systems.draw_manager->Draw(m_animsprite[1], 337, 355, 1);
}

State* VictoryState::NextState()
{
	return new GameState(m_systems);
}