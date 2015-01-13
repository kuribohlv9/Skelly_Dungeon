#include "stdafx.h"
#include "DeadState.h"
#include "InputManager.h"
#include "Keyboard.h"
#include "DrawManager.h"


DeadState::DeadState(System& systems)
{
	m_systems = systems;
	SDL_SetRenderDrawColor(m_systems.draw_manager->GetRenderer(), 255, 0, 0, 255);
}


DeadState::~DeadState()
{
}

bool DeadState::Update(float deltatime)
{
	if (m_systems.input_manager->GetKeyboard()->IsKeyDown(0) == true)
	{
		return false;
	}
	return true;
}

void DeadState::Draw()
{

}

State* DeadState::NextState()
{
	return nullptr;
}