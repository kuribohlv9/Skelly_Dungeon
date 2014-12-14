// main.cpp

#include "stdafx.h"
#include "Engine.h"

// !! bit.ly/1vSPzOk !! 

// topics
// == previous:
// Engine
//   DrawManager
//   InputManager
//     Mouse
//     Keyboard

// == today: 
//   StateManager
//     State 
//     GameState
//   TextureManager
//   CollisionManager


int main(int argc, char* argv[])
{
	Engine engine;
	if (engine.Initialize())
		engine.Update();
	engine.Shutdown();

	return 0;
}
