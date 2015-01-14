// SpriteText.h

#pragma once
#ifndef SPRITETEXT_H_INCLUDED
#define SPRITETEXT_H_INCLUDED

#include "Sprite.h"

class SpriteText : public Sprite

{
public:
	SpriteText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int r, int g, int b);
	~SpriteText();

	SDL_Color GetColor();
	std::string GetText();
	void Set(const std::string& text);
	void Set(int colorR, int colorG, int colorB);														//method to change colour
	void Set(const std::string& text, int colorR, int colorG, int colorB);
	void Set(float a);
	void Set(int a);
	void Set(char a);


private:
	void UpdateTexture();
	SDL_Renderer* m_renderer;
	TTF_Font* m_font;
	SDL_Color m_color;
	std::string m_text;
};

#endif // SPRITETEXT