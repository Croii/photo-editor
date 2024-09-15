#include "Application.h"

#include <iostream>
#include <string>

int main()
{

	Application engine;
	while (engine.running())
	{
		//Event handling
		engine.update();
		engine.render();
	}
	return 0;
}