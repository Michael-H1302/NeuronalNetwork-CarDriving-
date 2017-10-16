#include "App.h"

App::App()
{
	_AppWindow.create(sf::VideoMode(1920, 1080), "CarNeuronalNetwork");
	_AppWindow.setFramerateLimit(60);
}

void App::Run()
{
	this->Render();
	this->Update();
	this->HandleEvents();
}

bool App::IsOpen()
{
	return _AppWindow.isOpen();
}

/* ################ Private ################ */

void App::Render()
{
	_AppWindow.clear();

	_AppWindow.display();
}

void App::Update()
{

}

void App::HandleEvents()
{
	sf::Event event;
	while (_AppWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_AppWindow.close();
			return;
		}
	}
}