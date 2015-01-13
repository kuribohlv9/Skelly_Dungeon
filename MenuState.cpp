#include "stdafx.h"
#include "MenuState.h"
#include "GameState.h"
#include "InputManager.h"
#include "Keyboard.h"


MenuState::MenuState(System& systems)
{
	m_systems = systems;
}


MenuState::~MenuState()
{
}

bool MenuState::Update(float deltatime)
{
	if (m_systems.input_manager->GetKeyboard()->IsKeyDown(4) == true)
	{
		return false;
	}
	return true;
}

void MenuState::Draw()
{

}

State* MenuState::NextState()
{
	return new GameState(m_systems);
}