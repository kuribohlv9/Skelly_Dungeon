#include "stdafx.h"
#include "MenuState.h"
#include "GameState.h"
#include "InputManager.h"
#include "Keyboard.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "SpriteAnimation.h"


MenuState::MenuState(System& systems)
{
	m_systems = systems;
	//SpriteText* spritetext = m_systems.sprite_manager->CreateSprite("../Skelly_Dungeon/assets/LCD_Solid.ttf", 22, "Welcome to SKELLY DUNGEON", 255, 255, 255);
	//m_spriteText.push_back(spritetext);

	//Creates background image and animated start prompt
	Sprite* background = m_systems.sprite_manager->CreateSprite("../Skelly_Dungeon/assets/background.png", 0, 0, 1024, 768);
	m_sprite.push_back(background);

	background = m_systems.sprite_manager->CreateSprite("../Skelly_Dungeon/assets/bgtext.png", 0, 0, 1024, 768);
	m_sprite.push_back(background);

	SpriteAnimation* sprite = m_systems.sprite_manager->CreateAnimatedSprite("../Skelly_Dungeon/assets/pressenter.txt");
	sprite->SetAnimation("pressenter");
	m_animsprite.push_back(sprite);
}


MenuState::~MenuState()
{
}

bool MenuState::Update(float deltatime)
{
	m_animsprite[0]->Update(deltatime);

	if (m_systems.input_manager->GetKeyboard()->IsKeyDown(5) == true)
	{
		return false;
	}
	return true;
}

void MenuState::Draw()
{
	//Draws background image and animated start prompt
	m_systems.draw_manager->Draw(m_sprite[0], 0, 0, 1);
	m_systems.draw_manager->Draw(m_sprite[1], 0, 0, 1);
	m_systems.draw_manager->Draw(m_animsprite[0], 280, 380, 1);
}

State* MenuState::NextState()
{
	return new GameState(m_systems);

}