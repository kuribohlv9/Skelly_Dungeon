// Keyboard.cpp

#include "stdafx.h"
#include "Keyboard.h"

Keyboard::Keyboard()
{
	for (int i = 0; i < sizeof(m_keys); i++)
		m_keys[i] = false;
}

bool Keyboard::IsKeyDown(int index)
{
	if (index < 0 || index >= sizeof(m_keys))
		return false;
	return m_keys[index];
}

void Keyboard::SetKeyboard(int index, bool state)
{
	m_keys[index] = state;
}
