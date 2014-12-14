// Sprite.h

#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

class Sprite
{
public:
	Sprite(SDL_Texture* texture);
	~Sprite();

	SDL_Rect* GetRegion();
	SDL_Texture* GetTexture();

private:
	SDL_Rect m_region;
	SDL_Texture* m_texture;
};

#endif // SPRITE_H_INCLUDED
