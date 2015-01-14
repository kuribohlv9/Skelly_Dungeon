// SpriteText.cpp

#include "stdafx.h"
#include "SpriteText.h"


SpriteText::SpriteText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int r, int g, int b) : Sprite(nullptr)			// scope at the end, we're specifiying what ctor we want to use from Sprite.h
{																																		// we use nullptr so Sprite(SDL_Texture* texture) from Sprite.h is used
	m_renderer = renderer;
	m_font = font;
	Set(text, r, g, b);
}
SpriteText::~SpriteText()
{

}

SDL_Color SpriteText::GetColor()
{
	return m_color;
}
std::string SpriteText::GetText()
{
	return m_text;
}
void SpriteText::Set(const std::string& text)

{
	m_text = text;
	UpdateTexture();
}
void SpriteText::Set(const std::string& text, int colorR, int colorG, int colorB)														//method to change colour

{
	m_text = text;
	m_color.r = colorR;
	m_color.g = colorG;
	m_color.b = colorB;
	UpdateTexture();
}
void SpriteText::Set(float a)

{

}
void SpriteText::Set(int a)

{

}
void SpriteText::Set(char a)

{

}

void SpriteText::UpdateTexture()
{
	SDL_Surface* surface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_color);
	if (surface != nullptr)
	{
		SDL_DestroyTexture(m_texture);

		if (m_texture != nullptr)
		{
			SDL_Surface* optimizedSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ARGB4444, 0);

			m_texture = SDL_CreateTextureFromSurface(m_renderer, optimizedSurface);
			SDL_QueryTexture(m_texture, nullptr, nullptr, &m_region.w, &m_region.h);
	
			SDL_FreeSurface(surface);
			SDL_FreeSurface(optimizedSurface);
		}
	}
	else
	{
		const char* error = TTF_GetError();
	}
}