// Mouse.h

#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

class Mouse
{
	friend class InputManager;

public:
	Mouse();

	int GetX();
	int GetY();
	bool IsButtonDown(int index);

private:
	void SetXY(int x, int y);
	void SetButton(int index, bool state);

private:
	bool m_buttons[3];
	int m_x;
	int m_y;
};

#endif // MOUSE_H_INCLUDED
