// main.cpp

#include "stdafx.h"
#include "Engine.h"

// !! bit.ly/1vSPzOk !! 


int main(int argc, char* argv[])
{
	Engine engine;
	if (engine.Initialize())
		engine.Update();
	engine.Shutdown();

	return 0;
}
