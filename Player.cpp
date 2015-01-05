#include "stdafx.h"
#include "Player.h"
#include "Collider.h"
#include "Sprite.h"
#include "Keyboard.h"
#include "SpriteAnimation.h"


Player::Player(Keyboard* keyboard, SpriteAnimation* sprite)
{
	//Starting point
	m_x = 100.0f;
	m_y = 100.0f;

	//Set the players initial speed
	m_speed = 500.0f;

	//Set Directions
	m_directionX = 0.0f;
	m_directionY = 0.0f;

	//Set sprite and keyboard
	m_sprite = sprite;
	m_keyboard = keyboard;

	//Initialize Collider
	m_collider = new Collider(0, 0);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w, m_sprite->GetRegion()->h);

	//Set visible
	m_visible = true;

	HeartCounter = 4;																				// sets starting HeartCounter to 4
	m_attacking = false;
	m_attackTimer = 0.0f;
}


Player::~Player()
{
	if (m_collider)
	{
		delete m_collider;
		m_collider = nullptr;
	}
}

void Player::Update(float deltatime)
{
	//Set the direction to zero so we won't speed up
	m_directionX = 0;
	m_directionY = 0;

	//Look at what keys are down and add to that direction
	std::string direction;

	if (m_keyboard->IsKeyDown(2))
	{
		//Left
		m_directionX -= 1;
		direction = "left";
	}
	else if (m_keyboard->IsKeyDown(3))
	{
		//Right
		m_directionX += 1;
		direction = "right";
	}
	
	else if (m_keyboard->IsKeyDown(0))
	{
		//Up
		m_directionY -= 1;
		direction = "up";
	}
	else if (m_keyboard->IsKeyDown(1))
	{
		//Down
		m_directionY += 1;
		direction = "down";
	}

	if (m_keyboard->IsKeyDown(4))
	{
		
		//Attacks in the direction the player is moving in
		std::string attack = m_sprite->GetAnimationName() + "Attack";
		m_sprite->SetAnimation(attack);
//		m_attacking = true;
	}

	if (direction != m_last_direction)
	{
		m_sprite->SetAnimation(direction);
		m_last_direction = direction;
	}

	//Normalize the direction so diagonal movement is at normal speed
	float lenght = sqrt(m_directionX * m_directionX + m_directionY * m_directionY);

	//if not division by zero
	if (lenght != 0.0f)
	{
		//Normalize
		m_directionX /= lenght;
		m_directionY /= lenght;
	}

	//Change the players position in X and Y based on the direction, speed and deltatime
	m_x += (m_directionX * m_speed * deltatime);
	m_y += (m_directionY * m_speed * deltatime);

	//Update the collider
	m_collider->SetPosition(m_x, m_y);

}

Sprite* Player::GetSprite()
{
	return m_sprite;
}

SpriteAnimation* Player::GetAniSprite()
{
	return m_sprite;
}

Collider* Player::GetCollider()
{
	return m_collider;
}

float Player::GetX()
{
	return m_x;
}

float Player::GetY()
{
	return m_y;
}

bool Player::IsVisible()
{
	return m_visible;
}

EEntityType Player::GetType()
{
	return ENTITY_PLAYER;
}

void Player::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void Player::SetHearts(int change)
{
	HeartCounter+= change;																				// using this function we can change the value of HeartCounter from GameState
}

float Player::GetDirectionX()
{
	return m_directionX;
}
float Player::GetDirectionY()
{
	return m_directionY;
}