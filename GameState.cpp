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
#include "Sword.h"
#include "Player.h"
#include "Item.h"
#include "Wall.h"

#include "Collider.h"
#include "CollisionManager.h"
GameState::GameState(System& system)
{
	m_systems = system;

	//Load player sprite information
	std::string filename = "../Skelly_Dungeon/assets/Player.txt";

	//Create player sprite
	SpriteAnimation* sprite = m_systems.sprite_manager->CreateAnimatedSprite(filename);
	sprite->SetAnimation("down");

	//Create player
	Player* player = new Player(m_systems.input_manager->GetKeyboard(), sprite);
	m_entities.push_back(player);

	//Load Hearts sprite information
	filename = "../Skelly_Dungeon/assets/Heart.txt";

	//Create heart sprite
	sprite = m_systems.sprite_manager->CreateAnimatedSprite(filename);
	sprite->SetAnimation("heart");

	//Create heart
	Heart* heart = new Heart(sprite, 50, 50);																// makes a new heart with set a giving position of 200x300
	m_entities.push_back(heart);																			// adds heart sprite to the vector

	//Create wall sprite
	filename = "../Skelly_Dungeon/assets/Wall.txt";

	sprite = m_systems.sprite_manager->CreateAnimatedSprite(filename);
	sprite->SetAnimation("wall");

	Wall* wall = new Wall(sprite);

	m_entities.push_back(wall);

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
	for (unsigned int i = m_entities.size()-1; i < -1; i--)
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
		if (m_entities[i]->GetType() == ENTITY_ITEM)
		{
			// if the collision manager detects a collision between player's hitbox and the item's hitbox
			if (CollisionManager::Check(m_entities[i]->GetCollider(), player->GetCollider(), overlapX, overlapY))
			{
				Item* item = dynamic_cast<Item*>(m_entities[i]);								// we dynamic cast the abstract class Item as class Entity so that we can access Entity's collider
				item->PickUp(player);															// we run Item's function, sending in our current player object as a parameter (function takes Player pointers as parameter)
			}
		}
		else if (m_entities[i]->GetType() == ENTITY_WALL)
		{
			if (CollisionManager::Check(m_entities[i]->GetCollider(), player->GetCollider(), overlapX, overlapY))
			{
				player->SetPosition(player->GetX() - overlapX, player->GetY() - overlapY);
			}
		}
	}
}
