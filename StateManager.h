// StateManager.h

#ifndef STATEMANAGER_H_INCLUDED
#define STATEMANAGER_H_INCLUDED

// forward declare
class State;

class StateManager
{
	friend class Engine;

public:
	StateManager();
	~StateManager();

	bool Update();
	void Draw();

private:
	void SetState(State* state);

private:
	State* m_active_state;
	unsigned int m_tick;
};

#endif // STATEMANAGER_H_INCLUDED
