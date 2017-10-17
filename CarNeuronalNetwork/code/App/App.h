#pragma once
#include <SFML\Graphics.hpp>
#include <ctime>

#include "Map\Map.h"

#include "..\Neurons\Neuron.h"
#include "..\Neurons\InputNeuron\InputNeuron.h"
#include "..\Neurons\HiddenNeuron\HiddenNeuron.h"
#include "..\Neurons\OutputNeuron\OutputNeuron.h"
#include "..\Neurons\Connection\Connection.h"

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

		void DeleteNetwork();
		void CreateNewNetwork();		
		void ResetCar();
		void CreateMap();
		void CreateCar();

		sf::RenderWindow _AppWindow;

		std::vector<sf::RectangleShape*> _Map;

		std::vector<InputNeuron*> _Input;
		std::vector<HiddenNeuron*> _Hidden;
		std::vector<OutputNeuron*> _Output;
		std::vector<Connection*> _Connections;

		std::vector<sf::RectangleShape*> _Sensors;
		sf::RectangleShape _Car;
		
		float _LastDistance, _CurrentDistance;
		sf::Clock _Timer;
};