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

#include "Player.h"

#include "Collider.h"
#include "CollisionManager.h"
GameState::GameState(System& system)
{
	m_systems = system;

	std::string filename = "../assets/Player.txt";

	SpriteAnimation* sprite = m_systems.sprite_manager->CreateAnimatedSprite(filename);
	sprite->SetAnimation("player");

	Player* player = new Player(m_systems.input_manager->GetKeyboard(), sprite);
	m_entities.push_back(player);

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
	int overlapX = 0, overlapY = 0;
	//if (CollisionManager::Check(ball->GetCollider(), paddle->GetCollider(), overlapX, overlapY))
	{
		
	}
	//else
	{
		
	}
}
