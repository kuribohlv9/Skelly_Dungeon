// SpriteManager.cpp

#include "stdafx.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "SpriteAnimation.h"

SpriteManager::SpriteManager(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

SpriteManager::~SpriteManager()
{
	// delete all remanining sprites
	auto it = m_sprites.begin();
	while (it != m_sprites.end())
	{
		delete (*it);
		++it;
	}
	m_sprites.clear();

	// destroy all loaded textures
	auto itr = m_textures.begin();
	while (itr != m_textures.end()) 
	{
		SDL_DestroyTexture(itr->second);
		++itr;
	}
	m_textures.clear();
}

Sprite* SpriteManager::CreateSprite(const std::string& filename, int x, int y, int w, int h)
{
	// first we search for if the texture is already loaded
	auto it = m_textures.find(filename);
	if (it == m_textures.end())
	{
		// if not, we create a new one
		SDL_Surface* surface = IMG_Load(filename.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);

		// we save the texture in the map for later reuse
		m_textures.insert(std::pair<std::string, SDL_Texture*>(filename, texture));

		// we can destroy the surface
		// since we now have a texture
		// that we use instead
		SDL_FreeSurface(surface);

		// now we get the texture so we can return it with a sprite
		it = m_textures.find(filename);
	}

	// then we create a new sprite 
	// with the texture associated
	Sprite* sprite = new Sprite(it->second);
	sprite->GetRegion()->x = x;
	sprite->GetRegion()->y = y;
	sprite->GetRegion()->w = w;
	sprite->GetRegion()->h = h;
	m_sprites.push_back(sprite);

	// return the newly newed sprite
	return sprite;
}

void SpriteManager::DestroySprite(Sprite* sprite)
{
	// we look through all sprites
	auto it = m_sprites.begin();
	while (it != m_sprites.end())
	{
		// if we find the right one 
		if ((*it) == sprite)
		{
			// we delete the sprite
			delete sprite;
			// and remove it from the vector
			m_sprites.erase(it);
			break;
		}
		++it;
	}
}

SpriteAnimation* SpriteManager::CreateAnimatedSprite(const std::string& filename)
{
	std::ifstream stream;
	stream.open(filename.c_str());
	if (!stream.is_open())
	{
		return nullptr;
	}
	std::string textureFilename;
	std::getline(stream, textureFilename);

	auto itr = m_textures.find(textureFilename);
	if (itr == m_textures.end())
	{
		// renderer surface format
		SDL_RendererInfo info;
		SDL_GetRendererInfo(m_renderer, &info);

		// if not, we create a new one
		SDL_Surface* surface = IMG_Load(textureFilename.c_str());
		SDL_ConvertSurfaceFormat(surface, info.texture_formats[0], 0);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);

		// we save the texture in the map for later reuse
		m_textures.insert(std::pair<std::string, SDL_Texture*>(textureFilename, texture));

		// we can destroy the surface
		// since we now have a texture
		// that we use instead
		SDL_FreeSurface(surface);

		// now we get the texture so we can return it with a sprite
		itr = m_textures.find(textureFilename);
	}
	SpriteAnimation* animSprite = new SpriteAnimation(itr->second);

	std::string line;
	while (!stream.eof())
	{
		std::string name;
		int count = 0;

		stream >> name;
		stream >> count;
		for (int i = 0; i < count; i++)
		{
			AnimFrame frame;
			stream >> frame.m_duration;
			stream >> frame.m_region.x;
			stream >> frame.m_region.y;
			stream >> frame.m_region.w;
			stream >> frame.m_region.h;

			animSprite->AddFrame(name, frame);
		}
	}

	stream.close();

	m_sprites.push_back(animSprite);

	return animSprite;

}