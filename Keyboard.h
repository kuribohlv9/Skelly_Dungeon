// Keyboard.h

#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

class Keyboard
{
	friend class InputManager;

public:
	Keyboard();

	bool IsKeyDown(int index);

private:
	void SetKeyboard(int index, bool state);

private:
	bool m_keys[256];
};

#endif // KEYBOARD_H_INCLUDED
