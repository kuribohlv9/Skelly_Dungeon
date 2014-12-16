#include "stdafx.h"
#include "Player.h"
#include "Collider.h"
#include "Sprite.h"
#include "Keyboard.h"
#include "SpriteAnimation.h"


Player::Player(Keyboard* keyboard, SpriteAnimation* sprite)
{
	m_x = 100.0f;
	m_y = 100.0f;
	m_speed = 2.0f;
	m_sprite = sprite;
	m_keyboard = keyboard;

	HeartCounter = 4;																				// sets starting HeartCounter to 4

	m_collider = new Collider(0, 0);
	m_collider->SetWidthHeight(m_sprite->GetRegion()->w, m_sprite->GetRegion()->h);

	m_visible = true;

}


Player::~Player()
{
}

void Player::Update(float deltatime)
{

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

void Player::SetHearts(int change)
{
	HeartCounter+= change;																				// using this function we can change the value of HeartCounter from GameState
}