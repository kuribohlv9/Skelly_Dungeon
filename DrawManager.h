// DrawManager.h

#ifndef DRAWMANAGER_H_INCLUDED
#define DRAWMANAGER_H_INCLUDED

class Sprite;

class DrawManager
{
public:
	DrawManager();
	~DrawManager();

	bool Initialize(int width, int height);
	void Shutdown();

	void Clear();
	void Present();

	void Draw(Sprite* sprite, int x, int y, int scale);

	SDL_Renderer* GetRenderer();

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};

#endif // DRAWMANAGER_H_INCLUDED
