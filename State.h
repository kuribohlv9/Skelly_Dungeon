// State.h

#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

class DrawManager;
class InputManager;
class SpriteManager;
class SoundManager;

struct System
{
	int width;
	int height;
	DrawManager* draw_manager;
	InputManager* input_manager;
	SpriteManager* sprite_manager;
	SoundManager* sound_manager;
};

class State
{
public:
	virtual ~State() {}
	virtual bool Update(float deltatime) = 0;
	virtual void Draw() = 0;
	virtual State* NextState() = 0;
};

#endif // STATE_H_INCLUDED
