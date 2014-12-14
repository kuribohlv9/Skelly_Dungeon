// InputManager.cpp

#include "stdafx.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "InputManager.h"

InputManager::InputManager()
{
	m_mouse = new Mouse;
	m_keyboard = new Keyboard;
}

InputManager::~InputManager()
{
	if (m_mouse)
	{
		delete m_mouse;
		m_mouse = nullptr;
	}
	if (m_keyboard)
	{
		delete m_keyboard;
		m_keyboard = nullptr;
	}
}

Mouse* InputManager::GetMouse()
{
	return m_mouse;
}

Keyboard* InputManager::GetKeyboard()
{
	return m_keyboard;
}

void InputManager::SetMousePosition(int x, int y)
{
	m_mouse->SetXY(x, y);
}

void InputManager::SetMouseButton(int index, bool state)
{
	m_mouse->SetButton(index, state);
}

void InputManager::SetKeyboard(int key, bool state)
{
	m_keyboard->SetKeyboard(key, state);
}
