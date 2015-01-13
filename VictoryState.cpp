#include "stdafx.h"
#include "VictoryState.h"
#include "GameState.h"
#include "Keyboard.h"
#include "InputManager.h"
#include "DrawManager.h"


VictoryState::VictoryState(System& systems)
{
	m_systems = systems;
	SDL_SetRenderDrawColor(m_systems.draw_manager->GetRenderer(), 0, 255, 0, 255);
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

}

State* VictoryState::NextState()
{
	return new GameState(m_systems);
}