#include "stdafx.h"
#include "Player.h"
#include "Collider.h"
#include "Sprite.h"
#include "Keyboard.h"
#include "SpriteAnimation.h"
#include "SoundClip.h"


Player::Player(Keyboard* keyboard, SpriteAnimation* sprite, SoundClip* sClip)
{
	//Starting point
	m_x = 100.0f;
	m_y = 200.0f;

	//Set the players initial speed
	m_speed = 500.0f;

	//Set sprite and keyboard
	m_sprite = sprite;
	m_keyboard = keyboard;

	//Initialize Collider
	m_collider = new Collider(0, 0);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w, m_sprite->GetRegion()->h);

	//We create this now and set it's position when we attack
	m_swordCollider = new Collider(0, 0);

	//Set visible
	m_visible = true;

	m_isInvincible = false;

	HeartCounter = 4;																				// sets starting HeartCounter to 4
	m_attackTimer = 0.0f;

	m_state = STATE_NORMAL;

	m_soundClip = sClip;
}


Player::~Player()
{
	if (m_collider)
	{
		delete m_collider;
		m_collider = nullptr;
	}
	if (m_swordCollider)
	{
		delete m_swordCollider;
		m_swordCollider = nullptr;
	}
}

void Player::Update(float deltatime)
{
	switch (m_state)
	{
	case STATE_NORMAL:
	{
		//Set the direction to zero so we won't speed up
		float directionX = 0;
		float directionY = 0;

		//Look at what keys are down and add to that direction
		if (m_keyboard->IsKeyDown(2))
		{
			//Left
			directionX -= 1;
			m_direction = "left";
		}
		else if (m_keyboard->IsKeyDown(3))
		{
			//Right
			directionX += 1;
			m_direction = "right";
		}
		else if (m_keyboard->IsKeyDown(0))
		{
			//Up
			directionY -= 1;
			m_direction = "up";
		}
		else if (m_keyboard->IsKeyDown(1))
		{
			//Down
			directionY += 1;
			m_direction = "down";
		}

		if (m_keyboard->IsKeyDown(4))
		{
			if (m_direction == "left")
			{
				m_swordCollider->SetPosition(m_x - 11*5, m_y +7.5*5 -1.5*5);
				m_swordCollider->SetWidthHeight(11, 3);
			}
			else if (m_direction == "right")
			{
				m_swordCollider->SetPosition(m_x + 16 * 5, m_y + 7.5 * 5 - 1.5 * 5);
				m_swordCollider->SetWidthHeight(11, 3);
			}
			else if (m_direction == "up")
			{
				m_swordCollider->SetPosition(m_x+ 8*5 - 1.5 *5, m_y - 10*5);
				m_swordCollider->SetWidthHeight(3, 11);
			}
			else if (m_direction == "down")
			{
				m_swordCollider->SetPosition(m_x + 8*5 - 1.5 * 5, m_y + 16*5);
				m_swordCollider->SetWidthHeight(3, 11);
			}

			//Attacks in the direction the player is moving in
			std::string attack = m_direction + "Attack";

			//sends the player into attacking state;
			m_sprite->SetAnimation(attack);
			
			m_state = STATE_ATTACKING;
			m_attackTimer = 0;
			m_soundClip->Play();																			// plays the soundclip for attacking, which is loaded in GameState and sent in via the player's ctor
			break;
		}

		
		if (m_direction != m_last_direction)
		{
			//Stops the sprite's animation from restarting unless they change direction
			m_sprite->SetAnimation(m_direction);
			m_last_direction = m_direction;
		}
		if (directionX == 0 && directionY == 0)
		{
			//This stops the sprite from animating
			//m_sprite->SetAnimation("Nope");
			//m_last_direction = "lolwut";
			m_sprite->SetAnimate(false);
		}
		else
		{
			m_sprite->SetAnimate(true);
		}

		//Normalize the direction so diagonal movement is at normal speed
		float lenght = sqrt(directionX * directionX + directionY * directionY);

		//if not division by zero
		if (lenght != 0.0f)
		{
			//Normalize
			directionX /= lenght;
			directionY /= lenght;
		}

		//Change the players position in X and Y based on the direction, speed and deltatime
		m_x += (directionX * m_speed * deltatime);
		m_y += (directionY * m_speed * deltatime);

		//Update the collider
		m_collider->SetPosition(m_x, m_y);
		break;
	}

	case STATE_ATTACKING:
	{
		m_attackTimer += deltatime;
		if (m_attackTimer > 0.25f)
		{
			m_state = STATE_NORMAL;
			m_sprite->SetAnimation(m_last_direction);
		}
		break;
	}
	case STATE_DAMAGE:
	{
		m_damageTimer += deltatime;

		if (m_direction == "right")
		{
			m_x -= (m_speed*deltatime);
		}
		else if (m_direction == "left")
		{
			m_x += (m_speed*deltatime);
		}
		else if (m_direction == "down")
		{
			m_y -= (m_speed*deltatime);
		}
		else if (m_direction == "up")
		{
			m_y += (m_speed*deltatime);
		}

		m_collider->SetPosition(m_x, m_y);

		if (m_damageTimer > 0.5f)
		{
			m_state = STATE_NORMAL;
		}
		break;
	}

	}
	if (m_damageTimer > 0)
	{
		m_damageTimer += deltatime;
		if (m_damageTimer > 1.5f)
		{
			m_isInvincible = false;
			m_damageTimer = 0;
		}
	}
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

Collider* Player::GetSwordCollider()
{
	return m_swordCollider;
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

int Player::GetHearts()
{
	return HeartCounter;
}

PlayerState Player::GetState()
{
	return m_state;
}

void Player::SetState(PlayerState state, float x, float y)
{
	m_state = state;
	m_attackTimer = 0;
	m_isInvincible = true;
	/*if (x < 0)
	{
		m_direction = "left";
	}
	else if (x > 0)
	{
		m_direction = "right";
	}
	else if (y < 0)
	{
		m_direction = "up";
	}
	else if (y > 0)
	{
		m_direction = "down";
	}*/
}

bool Player::IsInvincible()
{
	return m_isInvincible;
}