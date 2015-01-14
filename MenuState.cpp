#include "stdafx.h"
#include "MenuState.h"
#include "GameState.h"
#include "InputManager.h"
#include "Keyboard.h"
#include "SpriteManager.h"
#include "DrawManager.h"


MenuState::MenuState(System& systems)
{
	m_systems = systems;
	//SpriteText* spritetext = m_systems.sprite_manager->CreateSprite("../Skelly_Dungeon/assets/LCD_Solid.ttf", 22, "Welcome to SKELLY DUNGEON", 255, 255, 255);
	//m_spriteText.push_back(spritetext);

	
	Sprite* background = m_systems.sprite_manager->CreateSprite("../Skelly_Dungeon/assets/background.png", 0, 0, 1024, 768);
	m_sprite.push_back(background);
}


MenuState::~MenuState()
{
}

bool MenuState::Update(float deltatime)
{
	if (m_systems.input_manager->GetKeyboard()->IsKeyDown(5) == true)
	{
		return false;
	}
	return true;
}

void MenuState::Draw()
{
	m_systems.draw_manager->Draw(m_sprite[0], 0, 0, 1);
}

State* MenuState::NextState()
{
	return new GameState(m_systems);

}