// SpriteManager.h

#ifndef SPRITEMANAGER_H_INCLUDED
#define SPRITEMANAGER_H_INCLUDED

class Sprite;
class SpriteAnimation;
class SpriteText;

class SpriteManager
{
	friend class DrawManager;

public:
	SpriteManager(SDL_Renderer* renderer);
	~SpriteManager();

	Sprite* CreateSprite(const std::string& filename, int x, int y, int w, int h);
	SpriteText* CreateSprite(const std::string &fontFilename, char size, const std::string &text, int colorR, int colorG, int colorB);
	void DestroySprite(Sprite* sprite);
	SpriteAnimation* CreateAnimatedSprite(const std::string& filename);

private:
	SDL_Renderer* m_renderer;
	std::vector<Sprite*> m_sprites;
	std::map<std::string, SDL_Texture*> m_textures;
	std::map<std::string, TTF_Font*> m_fonts;
};

#endif // SPRITEMANAGER_H_INCLUDED