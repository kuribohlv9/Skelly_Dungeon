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
#include "VictoryState.h"
#include "DeadState.h"

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
	m_scale = 5;

	SDL_SetRenderDrawColor(m_systems.draw_manager->GetRenderer(), 0x11, 0x12, 0x13, 0xff);

	m_skelly_dead = 0;

	// Plays the bg music
	std::string filename = "../Skelly_Dungeon/assets/windmill.wav";
	MusicClip* mClip = m_systems.sound_manager->CreateMusicClip(filename);
	mClip->Play();

	// Creates sword sound effect, stores it as sClip for use in Player.cpp
	filename = "../Skelly_Dungeon/assets/LOZ_Sword.wav";
	SoundClip* sClip = m_systems.sound_manager->CreateSoundClip(filename);

	// Creates sound fx and adds them as pairs with accompanying string names in the map m_sounds
	filename = "../Skelly_Dungeon/assets/LOZ_Get_Heart.wav";
	SoundClip* clip = m_systems.sound_manager->CreateSoundClip(filename);
	m_sounds.insert(std::pair<std::string, SoundClip*>("HeartSound", clip));								// Places the clip above into the m_sounds map as a pair so it can be recalled with the identifier "HeartSound"
	
	filename = "../Skelly_Dungeon/assets/LOZ_Hit.wav";
	clip = m_systems.sound_manager->CreateSoundClip(filename);
	m_sounds.insert(std::pair<std::string, SoundClip*>("Hit", clip));

	filename = "../Skelly_Dungeon/assets/LOZ_Hurt.wav";
	clip = m_systems.sound_manager->CreateSoundClip(filename);
	m_sounds.insert(std::pair<std::string, SoundClip*>("Hurt", clip));

	// Create RoomManager
	m_roomManager = new RoomManager();

	//Create player sprite
	filename = "../Skelly_Dungeon/assets/Player.txt";
	SpriteAnimation* sprite = m_systems.sprite_manager->CreateAnimatedSprite(filename);
	sprite->SetAnimation("down");

	//Create player
	Player* player = new Player(m_systems.input_manager->GetKeyboard(), sprite, sClip);
	m_entities.push_back(player);

	//Create heart sprite
	filename = "../Skelly_Dungeon/assets/Heart.txt";
	sprite = m_systems.sprite_manager->CreateAnimatedSprite(filename);
	sprite->SetAnimation("heart");
	m_roomManager->AddSprite("heart", sprite);

	//Create skeleton sprite
	filename = "../Skelly_Dungeon/assets/Skeleton.txt";
	sprite = m_systems.sprite_manager->CreateAnimatedSprite(filename);
	sprite->SetAnimation("skeleton");
	m_roomManager->AddSprite("Skelly", sprite);

	//Create wall sprite
	filename = "../Skelly_Dungeon/assets/Wall.txt";
	sprite = m_systems.sprite_manager->CreateAnimatedSprite(filename);
	sprite->SetAnimation("wall");
	m_roomManager->AddSprite("wall", sprite);
	
	//Create ground sprite
	filename = "../Skelly_Dungeon/assets/Ground.txt";
	sprite = m_systems.sprite_manager->CreateAnimatedSprite(filename);
	sprite->SetAnimation("ground");
	m_roomManager->AddSprite("ground", sprite);

	//Create room

	Room* room = m_roomManager->CreateRoom("../Skelly_Dungeon/assets/room.txt");

	m_room = room;
	NextRoom("room1");

	m_active = false;


	//Loads gui sprite info and stores them in the vector m_GUIVector

	sprite = m_systems.sprite_manager->CreateAnimatedSprite("../Skelly_Dungeon/assets/guiheart.txt");
	sprite->SetAnimation("guiheart");
	m_GUIVector.push_back(sprite);

	sprite = m_systems.sprite_manager->CreateAnimatedSprite("../Skelly_Dungeon/assets/life.txt");
	sprite->SetAnimation("life");
	m_GUIVector.push_back(sprite);

	sprite = m_systems.sprite_manager->CreateAnimatedSprite("../Skelly_Dungeon/assets/box.txt");
	sprite->SetAnimation("box");
	m_GUIVector.push_back(sprite);
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

	delete m_roomManager;
	m_roomManager = nullptr;
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
	}
	m_entities[0]->GetSprite()->Update(deltatime);
	m_roomManager->GetSprite("Skelly")->Update(deltatime);
	m_roomManager->GetSprite("heart")->Update(deltatime);

	// we always do collision checking after updating 
	// positions et al in entities
	CollisionChecking();

	Player* player = static_cast<Player*>(m_entities[0]);
	if (player->GetHearts() <= 0)
	{
		return false;
	}
	else if (m_skelly_dead > 20)
	{
		return false;
	}

	return true;
}

void GameState::Draw()
{
	//To create the illusion of a camera we draw everything offset to the player
	int BGoffsetX = 470;
	int BGoffSetY = 320;

	DrawBackground(BGoffsetX, BGoffSetY);

	for (unsigned int i = m_entities.size()-1; i < -1; i--)
	{
		if (!m_entities[i]->IsVisible())
			continue;

		Sprite* sprite = m_entities[i]->GetSprite();
		if (sprite)
		{
			if (i != 0)
			{
				m_systems.draw_manager->Draw(sprite, m_entities[i]->GetX() - m_entities[0]->GetX() + BGoffsetX, m_entities[i]->GetY() - m_entities[0]->GetY() + BGoffSetY, m_scale);
			}
			else
			{
				m_systems.draw_manager->Draw(sprite, m_systems.width / 2 - m_entities[i]->GetSprite()->GetRegion()->w * 5 / 2, m_systems.height / 2 - m_entities[i]->GetSprite()->GetRegion()->h * 5 / 2, m_scale);
			}
		}
	}
	
	DrawGUI();																								// Runs the DrawGUI() function
}

void GameState::DrawGUI()
//Here will be code to draw the gui
{
	Player* player = static_cast<Player*>(m_entities[0]);													// Static casts the first element in m_entities, which is always player, to a pointer so we can access the Player class's functions ( GetHearts() )
	m_systems.draw_manager->Draw(m_GUIVector[2], 580, 35, m_scale);

	for (int i = 0; i < player->GetHearts(); i++)
	{
		m_systems.draw_manager->Draw(m_GUIVector[0], 600 + i * 80, 11, m_scale);
		
	}

}

void GameState::DrawBackground(int BGoffsetX, int BGoffSetY)
{
	

	for (int i = 0; i < m_room->GetHeight(); i++)
	{
		for (int j = 0; j < m_room->GetWidth(); j++)
		{
			if (m_room->GetTilemap()[i][j] == TILE_GROUND || m_room->GetTilemap()[i][j] == TILE_ENEMY)
			{
				m_systems.draw_manager->Draw(m_roomManager->GetSprite("ground"), j * 16 * m_scale - m_entities[0]->GetX() + BGoffsetX, i * 16 * m_scale - m_entities[0]->GetY() + BGoffSetY, m_scale);

			}
			else if (m_room->GetTilemap()[i][j] == TILE_WALL)
			{
				m_systems.draw_manager->Draw(m_roomManager->GetSprite("wall"), j * 16 * m_scale - m_entities[0]->GetX() + BGoffsetX, i * 16 * m_scale - m_entities[0]->GetY() + BGoffSetY, m_scale);
			}
		}
	}
}

State* GameState::NextState()
{
	Player* player = static_cast<Player*>(m_entities[0]);
	if (player->GetHearts() <= 0)
	{
		return new DeadState(m_systems);
	}
	return new VictoryState(m_systems);
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
				
				GetSoundClip("HeartSound")->Play();
				delete m_entities[i];															// deletes the dynamically allocated memory where the heart was stored in the vector
				m_entities.erase(m_entities.begin() + i);										// erase removes the pointer to the heart AND its position in the vector (otherwise there will be a memleak!)
			}
		}
		else if (m_entities[i]->GetType() == ENTITY_ENEMY)
		{
			if (CollisionManager::Check(m_entities[i]->GetCollider(), player->GetCollider(), overlapX, overlapY) && !player->IsInvincible())
			{
				GetSoundClip("Hurt")->Play();
				player->SetState(STATE_DAMAGE, overlapX, overlapY);
				player->SetHearts(-1);
			}
			if (player->GetState() == STATE_ATTACKING && CollisionManager::Check(m_entities[i]->GetCollider(), player->GetSwordCollider(), overlapX, overlapY))
			{
				
				Heart* heart = nullptr;
				GetSoundClip("Hit")->Play();
				if (static_cast<int>(player->GetX()) % 2 == 0)
				{
					heart = new Heart(m_roomManager->GetSprite("heart"), m_entities[i]->GetX(), m_entities[i]->GetY());
				}
				delete m_entities[i];
				m_entities.erase(m_entities.begin() + i);
				m_skelly_dead += 1;

				if (heart)
				{
					m_entities.push_back(heart);
				}
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
			player->GetCollider()->SetPosition(player->GetX(), player->GetY());
			NextRoom(m_room->GetDoor(i)->GetDestinationName());
		}
	}
}

void GameState::NextRoom(std::string name)
{
	//deallocate everything in the old room
	auto it = m_entities.begin();
	it++;
	while (it != m_entities.end())
	{
		delete *it;
		it++;
	}

	m_entities.erase(m_entities.begin() + 1, m_entities.end());

	m_room = m_roomManager->GetRoom(name);

	Player* player = static_cast<Player*>(m_entities[0]);

	std::vector<Entity*> tempVector = m_room->Load(m_scale, m_roomManager->GetSprite("Skelly"), player);

	auto itr = tempVector.begin();
	while (itr != tempVector.end())
	{
		m_entities.push_back(*itr);
		itr++;
	}
}

SoundClip* GameState::GetSoundClip(std::string name)														// a function for getting sound clips by referring to their string name, stored as a pair in the map m_sounds
{
	auto itr = m_sounds.find(name);
	return itr->second;
}
