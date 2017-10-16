#include <iostream>

#include "App\App.h"

int main()
{
	App app;

	while (app.IsOpen())
	{
		app.Run();
	}

	return 0;
}