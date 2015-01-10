// Engine.h

#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

// forward declares
class DrawManager;
class InputManager;
class StateManager;
class SpriteManager;
class SoundManager;

class Engine
{
public:
	Engine();
	~Engine();

	bool Initialize();
	void Shutdown();
	void Update();

private:
	void HandleEvents();

private:
	bool m_running;
	DrawManager* m_draw_manager;
	InputManager* m_input_manager;
	SpriteManager* m_sprite_manager;
	StateManager* m_state_manager;
	SoundManager* m_sound_manager;

};

#endif // ENGINE_H_INCLUDED
