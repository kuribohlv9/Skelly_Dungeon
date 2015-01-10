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
#include "RoomManager.h"
#include "SoundManager.h"
#include "SoundClip.h"

#include "Heart.h"
#include "Player.h"
#include "Item.h"
#include "Wall.h"
#include "Room.h"

#include "Enemy.h"
#include "Skeleton.h"
#include "Door.h"

#include "Collider.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "SoundClip.h"
#include "MusicClip.h"

GameState::GameState(System& system)
{
	m_systems = system;

	std::string soundfilename = "../Skelly_Dungeon/assets/windmill.wav";
	SoundClip* clip = m_systems.sound_manager->CreateSoundClip(soundfilename);
	clip->Play();

	m_roomManager = new RoomManager(m_systems.sprite_manager);



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

	m_roomManager->AddSprite("heart", sprite);

	//Create heart
	Heart* heart = new Heart(sprite, 50, 50);																// makes a new heart with set a giving position of 50x50
	m_entities.push_back(heart);																			// adds heart sprite to the vector

	//Load skeleton sprite information
	filename = "../Skelly_Dungeon/assets/Skeleton.txt";

	//Create skeleton sprite
	sprite = m_systems.sprite_manager->CreateAnimatedSprite(filename);
	sprite->SetAnimation("skeleton");

	//Create skeleton!!
	Skeleton* skeleton = new Skeleton(sprite, 400, 400);
	m_entities.push_back(skeleton);


	//Create wall sprite
	filename = "../Skelly_Dungeon/assets/Wall.txt";

	sprite = m_systems.sprite_manager->CreateAnimatedSprite(filename);
	sprite->SetAnimation("wall");

	m_roomManager->AddSprite("wall", sprite);

	//Wall* wall = new Wall(sprite, 300, 300);
	
	filename = "../Skelly_Dungeon/assets/Ground.txt";
	sprite = m_systems.sprite_manager->CreateAnimatedSprite(filename);
	sprite->SetAnimation("ground");

	m_roomManager->AddSprite("ground", sprite);

	//m_entities.push_back(wall);

	//Create room

	Room* room = m_roomManager->CreateRoom("../Skelly_dungeon/assets/room.txt");

	m_room = room;
	m_room->Load(m_systems.draw_manager->GetScale());

	m_active = false;
}

GameState::~GameState()
{
	auto it = m_entities.begin();
	while (it != m_entities.end())
	{
		delete (*it);
		++it;
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
		m_entities[i]->GetSprite()->Update(deltatime);
	}

	// we always do collision checking after updating 
	// positions et al in entities
	CollisionChecking();

	return true;
}

void GameState::Draw()
{
	int BGoffsetX = 470;
	int BGoffSetY = 320;
	for (int i = 0; i < m_room->GetHeight(); i++)
	{
		for (int j = 0; j < m_room->GetWidth(); j++)
		{
			if (m_room->GetTilemap()[i][j] == TILE_GROUND)
			{
				m_systems.draw_manager->Draw(m_roomManager->GetSprite("ground"), j * 16 * m_systems.draw_manager->GetScale() - m_entities[0]->GetX() + BGoffsetX, i * 16 * m_systems.draw_manager->GetScale() - m_entities[0]->GetY() + BGoffSetY);

			}
			else if (m_room->GetTilemap()[i][j] == TILE_WALL)
			{
				m_systems.draw_manager->Draw(m_roomManager->GetSprite("wall"), j * 16 * m_systems.draw_manager->GetScale() - m_entities[0]->GetX() + BGoffsetX, i * 16 * m_systems.draw_manager->GetScale() - m_entities[0]->GetY() + BGoffSetY);
			}
			else if (m_room->GetTilemap()[i][j] == TILE_DOOR)
			{
				m_systems.draw_manager->Draw(m_roomManager->GetSprite("heart"), j * 16 * m_systems.draw_manager->GetScale() - m_entities[0]->GetX() + BGoffsetX, i * 16 * m_systems.draw_manager->GetScale() - m_entities[0]->GetY() + BGoffSetY);
			}
		}
	}

	for (unsigned int i = m_entities.size()-1; i < -1; i--)
	{
		if (!m_entities[i]->IsVisible())
			continue;

		Sprite* sprite = m_entities[i]->GetSprite();
		if (sprite)
		{
			if (i != 0)
			{
				m_systems.draw_manager->Draw(sprite, m_entities[i]->GetX() - m_entities[0]->GetX() + BGoffsetX, m_entities[i]->GetY() - m_entities[0]->GetY() + BGoffSetY);
			}
			else
			{
				m_systems.draw_manager->Draw(sprite, m_systems.width / 2 - m_entities[i]->GetSprite()->GetRegion()->w * 5 / 2, m_systems.height / 2 - m_entities[i]->GetSprite()->GetRegion()->h * 5 / 2);
			}
		}
	}

}

void GameState::DrawGUI()
{

//Here will be code to draw the gui, using GetRenderer() and rectangles

	// use a for-loop for the hearts, draw only WHOLE hearts for now. Draw them from the sprite sheet.

}

State* GameState::NextState()
{
	return nullptr;
}


// private
void GameState::CollisionChecking()
{
	Player* player = static_cast<Player*>(m_entities[0]);
	float overlapX = 0, overlapY = 0;

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
	}
	std::vector<Collider*>* tempVector = m_room->GetCollider();
	for (int i = 0; i < tempVector->size(); i++)
	{
		if (CollisionManager::Check((*tempVector)[i], player->GetCollider(), overlapX, overlapY))
		{
			player->SetPosition((player->GetX() - overlapX), (player->GetY() - overlapY));
			player->GetCollider()->SetPosition(player->GetX(), player->GetY());
		}
	}
	for (int i = 0; i < m_room->GetDoorNumber(); i++)
	{
		if (CollisionManager::Check(m_room->GetDoor(i)->GetCollider(), player->GetCollider(), overlapX, overlapY))
		{
			player->SetPosition(m_room->GetDoor(i)->GetDestinationX(), m_room->GetDoor(i)->GetDestinationY());
			NextRoom(m_room->GetDoor(i)->GetDestinationName());
		}
		else if (m_entities[i]->GetType() == ENTITY_ENEMY)
		{
			if (CollisionManager::Check(m_entities[i]->GetCollider(), player->GetCollider(), overlapX, overlapY))
			{
				player->SetPosition((player->GetX() - overlapX), (player->GetY() - overlapY));
				player->GetCollider()->SetPosition(player->GetX(), player->GetY());
			}
		}
	}
	
}

void GameState::NextRoom(std::string name)
{
	delete m_room->GetCollider();

	m_room = m_roomManager->GetRoom(name);

	m_room->Load(m_systems.draw_manager->GetScale());
}
