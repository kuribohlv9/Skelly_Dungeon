// Sprite.cpp

#include "stdafx.h"
#include "Sprite.h"

Sprite::Sprite(SDL_Texture* texture)
{
	m_region.x = 0;
	m_region.y = 0;
	m_region.w = 0;
	m_region.h = 0;
	m_texture = texture;
}

Sprite::~Sprite()
{
}

SDL_Rect* Sprite::GetRegion()
{
	return &m_region;
}

SDL_Texture* Sprite::GetTexture()
{
	return m_texture;
}
