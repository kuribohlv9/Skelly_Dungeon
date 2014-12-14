// InputManager.h

#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED

// forward declares
class Mouse;
class Keyboard;

class InputManager
{
	friend class Engine;

public:
	InputManager();
	~InputManager();

	Mouse* GetMouse();
	Keyboard* GetKeyboard();

private:
	void SetMousePosition(int x, int y);
	void SetMouseButton(int index, bool state);
	void SetKeyboard(int key, bool state);

private:
	Mouse* m_mouse;
	Keyboard* m_keyboard;
};

#endif // INPUTMANAGER_H_INCLUDED
