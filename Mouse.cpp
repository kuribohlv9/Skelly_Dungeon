// Mouse.cpp

#include "stdafx.h"
#include "Mouse.h"

Mouse::Mouse()
{
	for (int i = 0; i < 3; i++)
		m_buttons[i] = false;
	m_x = 0;
	m_y = 0;
}

int Mouse::GetX()
{
	return m_x;
}

int Mouse::GetY()
{
	return m_y;
}

bool Mouse::IsButtonDown(int index)
{
	if (index < 0 || index > 2)
		return false;
	return m_buttons[index];
}

void Mouse::SetXY(int x, int y)
{
	m_x = x;
	m_y = y;
}

void Mouse::SetButton(int index, bool state)
{
	m_buttons[index] = state;
}
