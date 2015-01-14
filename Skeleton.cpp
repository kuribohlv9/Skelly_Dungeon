#include "stdafx.h"
#include "Skeleton.h"
#include "Enemy.h"
#include "Collider.h"
#include "Sprite.h"
#include "SpriteAnimation.h"
#include "Player.h"


Skeleton::Skeleton(SpriteAnimation* sprite, Player* player, float startX, float startY)
{
	m_player = player;
	m_sprite = sprite;

	m_attackTimer = 1;
	m_x = startX;
	m_y = startY;
	m_directionX = 0;
	m_directionY = 0;

	//Initialize Collider
	m_collider = new Collider(m_x, m_y);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w, m_sprite->GetRegion()->h);

	m_visible = true;

	m_state = STATE_PASSIVE;
}


Skeleton::~Skeleton()
{
	if (m_collider)
	{
		delete m_collider;
		m_collider = nullptr;
	}
}


void Skeleton::Update(float deltatime)
{
	//AI for the skeleton, using states
	switch (m_state)
	{
	case STATE_PASSIVE:
	{
		//If the player is within 160x160 pixels of the skeleton, enter aggressive state with attack timer
		if (abs(m_player->GetX() - m_x) < 200 && abs(m_player->GetY() - m_y) < 200)
		{
			m_state = STATE_AGGRESSIVE;
			m_attackTimer = 1;
		}
		break;
	}
	//Aggressive state
	case STATE_AGGRESSIVE:
	{
		m_attackTimer += deltatime;

		//If attack timer is appropriate
		if (m_attackTimer > 0.5f)
		{
			m_attackTimer = 0;
			//checks to see if deltaX between skeleton and player is greater than deltaY "". If so, skeleton moves toward player along the x axis
			if (abs(m_player->GetX() - m_x) > abs(m_player->GetY() - m_y))
			{
				if ((m_player->GetX() - m_x) > 0)
				{
					m_directionX = deltatime * 200.0f;
				}
				else
				{
					m_directionX = -(deltatime* 200.0f);
				}
				m_directionY = 0;
			}
			//if not, skeleton moves toward player along the y axis.
			else
			{
				if ((m_player->GetY() - m_y) > 0)
				{
					m_directionY = deltatime * 200.0f;
				}
				else
				{
					m_directionY = -(deltatime* 200.0f);
				}
				m_directionX = 0;
			}
			//Skeleton enters passive state if it is farther than 360 pixels from the player along either x or y axes
			if (abs(m_player->GetX() - m_x) > 360 || abs(m_player->GetY() - m_y) > 360)
			{
				m_directionX = 0;
				m_directionY = 0;
				m_state = STATE_PASSIVE;
			}
		}
		m_x += m_directionX;
		m_y += m_directionY;
		m_collider->SetPosition(m_x, m_y);
		break;
	}
	default:
		break;
	}
}

Sprite* Skeleton::GetSprite()
{
	return m_sprite;
}

Collider* Skeleton::GetCollider()
{
	return m_collider;
}

float Skeleton::GetX()
{
	return m_x;
}

float Skeleton::GetY()
{
	return m_y;
}

bool Skeleton::IsVisible()
{

	return m_visible;

}

void Skeleton::SetInvisible()
{
	m_visible = false;
}

EEntityType Skeleton::GetType()
{
	return ENTITY_ENEMY;
}