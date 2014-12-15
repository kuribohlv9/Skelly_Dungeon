// SpriteManager.h

#ifndef SPRITEMANAGER_H_INCLUDED
#define SPRITEMANAGER_H_INCLUDED

class Sprite;

class SpriteManager
{
	friend class DrawManager;

public:
	SpriteManager(SDL_Renderer* renderer);
	~SpriteManager();

	Sprite* CreateSprite(const std::string& filename, int x, int y, int w, int h);
	void DestroySprite(Sprite* sprite);

private:
	SDL_Renderer* m_renderer;
	std::vector<Sprite*> m_sprites;
	std::map<std::string, SDL_Texture*> m_textures;
};

#endif // SPRITEMANAGER_H_INCLUDED
// hiya