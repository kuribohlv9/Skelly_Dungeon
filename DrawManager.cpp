// DrawManager.cpp

#include "stdafx.h"
#include "Sprite.h"
#include "DrawManager.h"

DrawManager::DrawManager()
{
	m_window = nullptr;
	m_renderer = nullptr;
}

DrawManager::~DrawManager()
{
	Shutdown();
}

bool DrawManager::Initialize(int width, int height)
{
	m_window = SDL_CreateWindow("Arkanoid",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL);
	if (m_window == nullptr)
	{
		SDL_Log("ERROR: Could not create window!");
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
		SDL_Log("ERROR: Could not create renderer!");
		return false;
	}

	SDL_SetRenderDrawColor(m_renderer, 0x11, 0x12, 0x13, 0xff);

	return true;
}

void DrawManager::Shutdown()
{
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
	if (m_window != nullptr)
	{
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	}
}

void DrawManager::Clear()
{
	SDL_RenderClear(m_renderer);
}

void DrawManager::Present()
{
	SDL_RenderPresent(m_renderer);
}

void DrawManager::Draw(Sprite* sprite, int x, int y)
{
	SDL_Rect dest = { x, y, sprite->GetRegion()->w, sprite->GetRegion()->h };
	SDL_RenderCopy(m_renderer, sprite->GetTexture(), sprite->GetRegion(), &dest);
}

SDL_Renderer* DrawManager::GetRenderer()
{
	return m_renderer;
}
