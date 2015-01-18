// StateManager.cpp

#include "stdafx.h"
#include "State.h"
#include "StateManager.h"

StateManager::StateManager()
{
	m_active_state = nullptr;
	m_tick = SDL_GetTicks();
}

StateManager::~StateManager()
{
	if (m_active_state)
	{
		delete m_active_state;
		m_active_state = nullptr;
	}
}

bool StateManager::Update()
{
	if (!m_active_state)
		return false;

	// calculate deltatime
	unsigned int now = SDL_GetTicks();
	unsigned int delta = now - m_tick;
	float deltatime = delta * 0.001f;
	m_tick = now;

	// if we are not updating, ie we are exiting our active state, get the next state from the 
	if (!m_active_state->Update(deltatime))
		SetState(m_active_state->NextState());

	return true;
}

void StateManager::Draw()
{
	if (!m_active_state)
		return;
	m_active_state->Draw();
}

void StateManager::SetState(State* state)
{
	if (m_active_state)
		delete m_active_state;
	m_active_state = state;
}
