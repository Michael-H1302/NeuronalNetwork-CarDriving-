#include "App.h"

App::App()
{
	_AppWindow.create(sf::VideoMode(1920, 1080), "CarNeuronalNetwork");
	_AppWindow.setFramerateLimit(60);

	srand(static_cast<unsigned int>(time(NULL)));

	_Map.push_back(new sf::RectangleShape);
	_Map[_Map.size() - 1]->setPosition(100, 50);
	_Map[_Map.size() - 1]->setSize(sf::Vector2f(10, 900));
	_Map[_Map.size() - 1]->setFillColor(sf::Color(0, 0, 255));

	_Map.push_back(new sf::RectangleShape);
	_Map[_Map.size() - 1]->setPosition(1000, 50);
	_Map[_Map.size() - 1]->setSize(sf::Vector2f(10, 900));
	_Map[_Map.size() - 1]->setFillColor(sf::Color(0, 0, 255));

	_Map.push_back(new sf::RectangleShape);
	_Map[_Map.size() - 1]->setPosition(100, 50);
	_Map[_Map.size() - 1]->setSize(sf::Vector2f(900, 10));
	_Map[_Map.size() - 1]->setFillColor(sf::Color(0, 0, 255));

	_Map.push_back(new sf::RectangleShape);
	_Map[_Map.size() - 1]->setPosition(100, 950);
	_Map[_Map.size() - 1]->setSize(sf::Vector2f(900, 10));
	_Map[_Map.size() - 1]->setFillColor(sf::Color(0, 0, 255));

	_Map.push_back(new sf::RectangleShape);
	_Map[_Map.size() - 1]->setPosition(300, 700);
	_Map[_Map.size() - 1]->setSize(sf::Vector2f(10, 300));
	_Map[_Map.size() - 1]->setFillColor(sf::Color(0, 0, 255));

	_Map.push_back(new sf::RectangleShape);
	_Map[_Map.size() - 1]->setPosition(100, 450);
	_Map[_Map.size() - 1]->setSize(sf::Vector2f(300, 10));
	_Map[_Map.size() - 1]->setFillColor(sf::Color(0, 0, 255));


	this->CreateNewNetwork();

	_Car.setFillColor(sf::Color(255, 255, 255));
	_Car.setSize(sf::Vector2f(64, 64));
	_Car.setOrigin(32, 32);
	_Car.setPosition(200, 850);

	_Sensors.push_back(new sf::RectangleShape);
	_Sensors[_Sensors.size() - 1]->setFillColor(sf::Color(0, 255, 0));
	_Sensors[_Sensors.size() - 1]->setOrigin(sf::Vector2f(3, 96));
	_Sensors[_Sensors.size() - 1]->setSize(sf::Vector2f(3, 96));
	_Sensors[_Sensors.size() - 1]->setRotation(-45);
	_Sensors[_Sensors.size() - 1]->setPosition(_Car.getPosition());

	_Sensors.push_back(new sf::RectangleShape);
	_Sensors[_Sensors.size() - 1]->setFillColor(sf::Color(0, 255, 0));
	_Sensors[_Sensors.size() - 1]->setOrigin(sf::Vector2f(3, 96));
	_Sensors[_Sensors.size() - 1]->setSize(sf::Vector2f(3, 96));
	_Sensors[_Sensors.size() - 1]->setPosition(_Car.getPosition());

	_Sensors.push_back(new sf::RectangleShape);
	_Sensors[_Sensors.size() - 1]->setFillColor(sf::Color(0, 255, 0));
	_Sensors[_Sensors.size() - 1]->setOrigin(sf::Vector2f(1, 96));
	_Sensors[_Sensors.size() - 1]->setSize(sf::Vector2f(3, 96));
	_Sensors[_Sensors.size() - 1]->setRotation(45);
	_Sensors[_Sensors.size() - 1]->setPosition(_Car.getPosition());

	_LastDistance = 0;
	_LastTime = 0;
	_SameGeneration = 0;
	_Timer.restart();

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

	for (unsigned int c = 0; c < _Map.size(); c++)
	{
		_AppWindow.draw(*_Map[c]);
	}

	/* Car */
	_AppWindow.draw(_Car);
	for (unsigned int c = 0; c < _Sensors.size(); c++)
	{
		_AppWindow.draw(*_Sensors[c]);
	}

	_AppWindow.display();
}

void App::Update()
{
	/* Input Werte setzen */
	float Value1 = 4;//2
	_Sensors[0]->setFillColor(sf::Color(0, 255, 0));
	for (unsigned int c = 0; c < _Map.size(); c++)
	{
		if (_Sensors[0]->getGlobalBounds().intersects(_Map[c]->getGlobalBounds()))
		{
			_Sensors[0]->setFillColor(sf::Color(255, 0, 0));
			Value1 = 1;
		}
	}
	_Input[0]->SetValue(Value1);

	float Value2 = 4;//2
	_Sensors[1]->setFillColor(sf::Color(0, 255, 0));
	for (unsigned int c = 0; c < _Map.size(); c++)
	{
		if (_Sensors[1]->getGlobalBounds().intersects(_Map[c]->getGlobalBounds()))
		{
			_Sensors[1]->setFillColor(sf::Color(255, 0, 0));
			Value2 = 1;
		}
	}
	_Input[1]->SetValue(Value2);

	float Value3 = 4;//2
	_Sensors[2]->setFillColor(sf::Color(0, 255, 0));
	for (unsigned int c = 0; c < _Map.size(); c++)
	{
		if (_Sensors[2]->getGlobalBounds().intersects(_Map[c]->getGlobalBounds()))
		{
			_Sensors[2]->setFillColor(sf::Color(255, 0, 0));
			Value3 = 1;
		}
	}
	_Input[2]->SetValue(Value3);

	for (unsigned int c = 0; c < _Connections.size(); c++)
	{
		_Connections[c]->Update();
	}

	_Sensors[0]->setPosition(_Car.getPosition());
	_Sensors[0]->setRotation(-45 + _Car.getRotation());
	_Sensors[1]->setPosition(_Car.getPosition());
	_Sensors[1]->setRotation(_Car.getRotation());
	_Sensors[2]->setPosition(_Car.getPosition());
	_Sensors[2]->setRotation(45 + _Car.getRotation());

	if (_Output[0]->GetValue() > 0.5f)//0.7
	{
		_Car.rotate(1);
	}
	if (_Output[0]->GetValue() < 0.5f)//0.3
	{
		_Car.rotate(-1);
	}

	float Speed = _Output[1]->GetValue();
	float Radiant = ((2 * 3.14f) / 360) * _Car.getRotation();
	float YMovement = cos(Radiant) + 0.5f * Speed;//5
	float XMovement = sin(Radiant) + 0.5f * Speed;//5
	
	if (_Car.getRotation() > 270 || _Car.getRotation() < 90)
	{
		YMovement = -YMovement;
	}
	else
	{
		YMovement = abs(YMovement);
	}
	_Car.move(XMovement, YMovement);

	/* Trainer um möglichst schnell vorwärts zu fahren */
	/*if (_Timer.getElapsedTime().asSeconds() > sf::seconds(5).asSeconds())
	{
		float Distance = 850 - _Car.getPosition().y;
		std::cout << "Distance: " << Distance << std::endl;

		// Mutate 

		if (Distance > _LastDistance)
		{
			std::cout << "Mutating..." << std::endl;
			for (unsigned int c = 0; c < _Connections.size(); c++)
			{
				_Connections[c]->Mutate();
			}
			this->ResetCar();

			_LastDistance = Distance;
			_Timer.restart();
			return;
		}

		if (Distance < _LastDistance && _LastDistance != 0)
		{
			std::cout << "Restoring and mutating..." << std::endl;
			for (unsigned int c = 0; c < _Connections.size(); c++)
			{
				_Connections[c]->Restore();
			}
			for (unsigned int c = 0; c < _Connections.size(); c++)
			{
				_Connections[c]->Mutate();
			}
			this->ResetCar();
			_Timer.restart();
			return;
		}

		// New Network 
		if (Distance < 0)
		{
			std::cout << "Creating new network..." << std::endl;
			this->DeleteNetwork();
			this->CreateNewNetwork();
			this->ResetCar();
			_Timer.restart();
			return;
		}	
	}
	*/

	/* Trainer um nicht gegen eine Wand zu fahren */
	for (unsigned int c = 0; c < _Map.size(); c++)
	{
		if (_Car.getGlobalBounds().intersects(_Map[c]->getGlobalBounds()))
		{
			float Distance = sqrt(pow(200 - _Car.getPosition().x, 2) + pow(850 - _Car.getPosition().y, 2));
			std::cout << "Distance: " << Distance << std::endl;

			if (Distance > _LastDistance)
			{
				_SameGeneration = 0;
				std::cout << "Mutating..." << std::endl;
				for (unsigned int c = 0; c < _Connections.size(); c++)
				{
					_Connections[c]->Mutate();
				}

				_LastDistance = Distance;
	
				this->ResetCar();
				_Timer.restart();

				return;
			}
			if (Distance < _LastDistance && _LastDistance != 0 && _SameGeneration < 10)
			{
				_SameGeneration++;
				std::cout << "Restoring and mutating..." << std::endl;

				for (unsigned int c = 0; c < _Connections.size(); c++)
				{
					_Connections[c]->Restore();
				}
				for (unsigned int c = 0; c < _Connections.size(); c++)
				{
					_Connections[c]->Mutate();
				}

				this->ResetCar();
				_Timer.restart();

				return;
			}
			if (Distance <= 0 || _SameGeneration >= 10)
			{
				_SameGeneration = 0;
				_LastDistance = 0;
				std::cout << "Creating new network..." << std::endl;
				this->DeleteNetwork();
				this->CreateNewNetwork();
				this->ResetCar();

				_Timer.restart();
			}
		}
	}
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

void App::CreateNewNetwork()
{
	_Input.push_back(new InputNeuron);
	_Input.push_back(new InputNeuron);
	_Input.push_back(new InputNeuron);

	_Hidden.push_back(new HiddenNeuron);
	_Hidden.push_back(new HiddenNeuron);
	_Hidden.push_back(new HiddenNeuron);
	_Hidden.push_back(new HiddenNeuron);
	_Hidden.push_back(new HiddenNeuron);

	_Output.push_back(new OutputNeuron);
	_Output.push_back(new OutputNeuron);

	for (unsigned int i = 0; i < _Input.size(); i++)
	{
		for (unsigned int c = 0; c < _Hidden.size(); c++)
		{
			_Connections.push_back(new Connection);
			_Connections[_Connections.size() - 1]->SetNeurons(_Input[i], _Hidden[c]);
		}
	}

	for (unsigned int i = 0; i < _Hidden.size(); i++)
	{
		for (unsigned int c = 0; c < _Output.size(); c++)
		{
			_Connections.push_back(new Connection);
			_Connections[_Connections.size() - 1]->SetNeurons(_Hidden[i], _Output[c]);
		}
	}
}

void App::DeleteNetwork()
{
	for (unsigned int c = 0; c < _Input.size(); c++)
	{
		delete _Input[c];
	}

	for (unsigned int c = 0; c < _Hidden.size(); c++)
	{
		delete _Hidden[c];
	}

	for (unsigned int c = 0; c < _Output.size(); c++)
	{
		delete _Output[c];
	}

	for (unsigned int c = 0; c < _Connections.size(); c++)
	{
		delete _Connections[c];
	}

	_Input.clear();
	_Hidden.clear();
	_Output.clear();
	_Connections.clear();
}

void App::ResetCar()
{
	_Car.setPosition(200, 850);
	_Car.setRotation(0);
}
