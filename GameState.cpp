// GameState.cpp

#include "stdafx.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "InputManager.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include "GameState.h"

#include "Heart.h"
#include "Player.h"
#include "Item.h"

#include "Collider.h"
#include "CollisionManager.h"
GameState::GameState(System& system)
{
	m_systems = system;

	std::string filename = "../Skelly_Dungeon/assets/Player.txt";

	SpriteAnimation* sprite = m_systems.sprite_manager->CreateAnimatedSprite(filename);
	sprite->SetAnimation("down");

	Player* player = new Player(m_systems.input_manager->GetKeyboard(), sprite);
	m_entities.push_back(player);

	filename = "../Skelly_Dungeon/assets/legendofzelda_link_sheet.png";

	Sprite* realSprite = m_systems.sprite_manager->CreateSprite(											// fetching the heart sprite from the png sheet
		filename, 240, 192, 16, 16);

	Heart* heart = new Heart(realSprite, 50, 50);															// makes a new heart with set a giving position of 200x300
	m_entities.push_back(heart);																			// adds heart sprite to the vector

	m_active = false;
}

GameState::~GameState()
{
	int c = 0;
	auto it = m_entities.begin();
	while (it != m_entities.end())
	{
		Sprite* sprite = (*it)->GetSprite();
		if (sprite)
			m_systems.sprite_manager->DestroySprite(sprite);
		delete (*it);
		++it;
		c++;
	}
	m_entities.clear();
}

bool GameState::Update(float deltatime)
{
	// update all entities
	for (unsigned int i = 0; i < m_entities.size(); i++)
	{
		if (!m_entities[i]->IsVisible())
			continue;

		// update
		m_entities[i]->Update(deltatime);
		m_entities[i]->GetSprite()->Update(0.5f);
	}

	// we always do collision checking after updating 
	// positions et al in entities
	CollisionChecking();

	return true;
}

void GameState::Draw()
{
	for (unsigned int i = 0; i < m_entities.size(); i++)
	{
		if (!m_entities[i]->IsVisible())
			continue;

		Sprite* sprite = m_entities[i]->GetSprite();
		if (sprite)
		{
			m_systems.draw_manager->Draw(sprite,
				m_entities[i]->GetX(),
				m_entities[i]->GetY());
		}
	}

}

State* GameState::NextState()
{
	return nullptr;
}


// private
void GameState::CollisionChecking()
{
	Player* player = static_cast<Player*>(m_entities[0]);
	int overlapX = 0, overlapY = 0;

	// looking through the entities vector for items
	for (int i = 1; i < m_entities.size(); i++)
	{
		if (m_entities[i]->GetType == ENTITY_ITEM)
		{
			// if the collision manager detects a collision between player's hitbox and the item's hitbox
			if (CollisionManager::Check(m_entities[i]->GetCollider(), player->GetCollider(), overlapX, overlapY))
			{
				Item* item = reinterpret_cast<Item*>(m_entities[i]);								// we reinterpret the abstract class Item as class Entity so that we can access Entity's collider
				item->PickUp(player);																// we run Item's function, sending in our current player object as a parameter (function takes Player pointers as parameter)
			}
		}
	}
	
			//increase player hp by one and make heart invisible

			
	//else
	{
		
	}
}
