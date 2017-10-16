#pragma once
#include <SFML\Graphics.hpp>

class App
{
	public:

		App();

		void Run();
		bool IsOpen();

	private:

		void Render();
		void Update();
		void HandleEvents();

		sf::RenderWindow _AppWindow;

};