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
	switch (m_state)
	{
	case STATE_PASSIVE:
	{
		if (abs(m_player->GetX() - m_x) < 160 && abs(m_player->GetY() - m_y) < 160)
		{
			m_state = STATE_AGGRESSIVE;
			m_attackTimer = 1;
		}
		break;
	}
	case STATE_AGGRESSIVE:
	{
		m_attackTimer += deltatime;

		if (m_attackTimer > 0.5f)
		{
			m_attackTimer = 0;
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