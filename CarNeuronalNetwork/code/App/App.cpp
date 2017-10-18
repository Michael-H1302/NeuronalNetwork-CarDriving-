#include "App.h"

App::App()
{
	_AppWindow.create(sf::VideoMode(1920, 1080), "CarNeuronalNetwork");
	//_AppWindow.setFramerateLimit(60);

	srand(static_cast<unsigned int>(time(NULL)));

	
	this->CreateMap();
	this->CreateNewNetwork();
	this->CreateCar();
	this->CreateVisualNetwork();

	_BestDistance = 0;
	_CurrentDistance = 0;
	_LastRotation = 0;
	_Balanced = true;
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

	/* Visualisierung */
	for (unsigned int c = 0; c < _InputNeuronsV.size(); c++)
	{
		_AppWindow.draw(*_InputNeuronsV[c]);
	}
	for (unsigned int c = 0; c < _HiddenNeuronsV.size(); c++)
	{
		_AppWindow.draw(*_HiddenNeuronsV[c]);
	}
	for (unsigned int c = 0; c < _OutputNeuronsV.size(); c++)
	{
		_AppWindow.draw(*_OutputNeuronsV[c]);
	}
	for (unsigned int c = 0; c < _ConnectionsV.size(); c++)
	{
		_AppWindow.draw(*_ConnectionsV[c]);
	}

	_AppWindow.display();
}

void App::Update()
{
	this->UpdateSensors();
	this->UpdateConnections();
	this->UpdateCar();
}

void App::UpdateSensors()
{
	/* Input Werte setzen */
	float Value1 = 9;
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

	float Value2 = 9;//2
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

	float Value3 = 9;//2
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

}

void App::UpdateCar()
{
	_Sensors[0]->setPosition(_Car.getPosition());
	_Sensors[0]->setRotation(-45 + _Car.getRotation());
	_Sensors[1]->setPosition(_Car.getPosition());
	_Sensors[1]->setRotation(_Car.getRotation());
	_Sensors[2]->setPosition(_Car.getPosition());
	_Sensors[2]->setRotation(45 + _Car.getRotation());

	float Rotation = (_Output[0]->GetValue() - 0.5f) * 2.5f;
	_Car.rotate(Rotation);

	float Speed = _Output[1]->GetValue();
	float Radiant = ((2 * 3.14f) / 360) * _Car.getRotation();
	float YMovement = cos(Radiant) * (abs(Speed) + 1.0f);//5
	float XMovement = sin(Radiant) * (abs(Speed) + 1.0f);//5

	if (_Car.getRotation() > 270 || _Car.getRotation() < 90)
	{
		YMovement = -YMovement;
	}
	else
	{
		YMovement = abs(YMovement);
	}

	_Car.move(XMovement, YMovement);
	_CurrentDistance = _CurrentDistance + abs(XMovement) + abs(YMovement);

	this->Trainer(Rotation);
}

void App::UpdateConnections()
{
	/* Connections updaten */
	for (unsigned int c = 0; c < _Connections.size(); c++)
	{
		_Connections[c]->Update();
	}

	/* Visualisierung updaten */
	for (unsigned int c = 0; c < _Connections.size(); c++)
	{
		_ConnectionsV[c]->setFillColor(sf::Color(static_cast<sf::Uint8>(85 * _Connections[c]->GetWeight()), static_cast<sf::Uint8>(255 - 85 * _Connections[c]->GetWeight()), 0));
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
	_Car.setPosition(225, 850);
	_Car.setRotation(0);
}

void App::CreateMap()
{
	_Map.push_back(new sf::RectangleShape);
	_Map[_Map.size() - 1]->setPosition(140, 600);
	_Map[_Map.size() - 1]->setSize(sf::Vector2f(5, 300));
	_Map[_Map.size() - 1]->setFillColor(sf::Color(0, 0, 255));

	_Map.push_back(new sf::RectangleShape);
	_Map[_Map.size() - 1]->setPosition(300, 700);
	_Map[_Map.size() - 1]->setSize(sf::Vector2f(5, 200));
	_Map[_Map.size() - 1]->setFillColor(sf::Color(0, 0, 255));

	_Map.push_back(new sf::RectangleShape);
	_Map[_Map.size() - 1]->setPosition(140, 900);
	_Map[_Map.size() - 1]->setSize(sf::Vector2f(165, 5));
	_Map[_Map.size() - 1]->setFillColor(sf::Color(0, 0, 255));

	std::vector<sf::RectangleShape*> Temp;

	Temp = Map::DrawLine(sf::Vector2f(300, 700), sf::Vector2f(450, 550));
	for (unsigned int c = 0; c < Temp.size(); c++)
	{
		_Map.push_back(Temp[c]);
	}
	Temp.clear();

	Temp = Map::DrawLine(sf::Vector2f(140, 600), sf::Vector2f(350, 350));
	for (unsigned int c = 0; c < Temp.size(); c++)
	{
		_Map.push_back(Temp[c]);
	}
	Temp.clear();

	_Map.push_back(new sf::RectangleShape);
	_Map[_Map.size() - 1]->setPosition(350, 350);
	_Map[_Map.size() - 1]->setSize(sf::Vector2f(300, 5));
	_Map[_Map.size() - 1]->setFillColor(sf::Color(0, 0, 255));

	_Map.push_back(new sf::RectangleShape);
	_Map[_Map.size() - 1]->setPosition(450, 550);
	_Map[_Map.size() - 1]->setSize(sf::Vector2f(50, 5));
	_Map[_Map.size() - 1]->setFillColor(sf::Color(0, 0, 255));

	Temp = Map::DrawLine(sf::Vector2f(650, 350), sf::Vector2f(850, 650));
	for (unsigned int c = 0; c < Temp.size(); c++)
	{
		_Map.push_back(Temp[c]);
	}
	Temp.clear();

	Temp = Map::DrawLine(sf::Vector2f(500, 550), sf::Vector2f(650, 700));
	for (unsigned int c = 0; c < Temp.size(); c++)
	{
		_Map.push_back(Temp[c]);
	}
	Temp.clear();

	_Map.push_back(new sf::RectangleShape);
	_Map[_Map.size() - 1]->setPosition(850, 650);
	_Map[_Map.size() - 1]->setSize(sf::Vector2f(5, 50));
	_Map[_Map.size() - 1]->setFillColor(sf::Color(0, 0, 255));

	_Map.push_back(new sf::RectangleShape);
	_Map[_Map.size() - 1]->setPosition(650, 700);
	_Map[_Map.size() - 1]->setSize(sf::Vector2f(5, 100));
	_Map[_Map.size() - 1]->setFillColor(sf::Color(0, 0, 255));

	Temp = Map::DrawLine(sf::Vector2f(850, 700), sf::Vector2f(950, 815));
	for (unsigned int c = 0; c < Temp.size(); c++)
	{
		_Map.push_back(Temp[c]);
	}
	Temp.clear();

	Temp = Map::DrawLine(sf::Vector2f(650, 800), sf::Vector2f(800, 950));
	for (unsigned int c = 0; c < Temp.size(); c++)
	{
		_Map.push_back(Temp[c]);
	}
	Temp.clear();

	_Map.push_back(new sf::RectangleShape);
	_Map[_Map.size() - 1]->setPosition(950, 815);
	_Map[_Map.size() - 1]->setSize(sf::Vector2f(150, 5));
	_Map[_Map.size() - 1]->setFillColor(sf::Color(0, 0, 255));

	_Map.push_back(new sf::RectangleShape);
	_Map[_Map.size() - 1]->setPosition(800, 950);
	_Map[_Map.size() - 1]->setSize(sf::Vector2f(200, 5));
	_Map[_Map.size() - 1]->setFillColor(sf::Color(0, 0, 255));
}

void App::CreateCar()
{
	_Car.setFillColor(sf::Color(255, 255, 255));
	_Car.setSize(sf::Vector2f(64, 64));
	_Car.setOrigin(32, 32);
	this->ResetCar();

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
	
}

void App::CreateVisualNetwork()
{
	for (unsigned int y = 100; y < 220; y = y + 40)
	{
		_InputNeuronsV.push_back(new sf::RectangleShape);
		_InputNeuronsV[_InputNeuronsV.size() - 1]->setSize(sf::Vector2f(16, 16));
		_InputNeuronsV[_InputNeuronsV.size() - 1]->setFillColor(sf::Color(0, 255, 0));
		_InputNeuronsV[_InputNeuronsV.size() - 1]->setPosition(1200, static_cast<float>(y));
		_InputNeuronsV[_InputNeuronsV.size() - 1]->setOrigin(8, 8);
	}

	for (unsigned int y = 60; y < 260; y = y + 40)
	{
		_HiddenNeuronsV.push_back(new sf::RectangleShape);
		_HiddenNeuronsV[_HiddenNeuronsV.size() - 1]->setSize(sf::Vector2f(16, 16));
		_HiddenNeuronsV[_HiddenNeuronsV.size() - 1]->setFillColor(sf::Color(150, 150, 150));
		_HiddenNeuronsV[_HiddenNeuronsV.size() - 1]->setPosition(1350, static_cast<float>(y));
		_HiddenNeuronsV[_HiddenNeuronsV.size() - 1]->setOrigin(8, 8);
	}

	for (unsigned int y = 100; y < 220; y = y + 40)
	{
		_OutputNeuronsV.push_back(new sf::RectangleShape);
		_OutputNeuronsV[_OutputNeuronsV.size() - 1]->setSize(sf::Vector2f(16, 16));
		_OutputNeuronsV[_OutputNeuronsV.size() - 1]->setFillColor(sf::Color(255, 0, 0));
		_OutputNeuronsV[_OutputNeuronsV.size() - 1]->setPosition(1500, static_cast<float>(y));
		_OutputNeuronsV[_OutputNeuronsV.size() - 1]->setOrigin(8, 8);
	}

	for (unsigned int c = 0; c < _InputNeuronsV.size(); c++)
	{
		for (unsigned int i = 0; i < _HiddenNeuronsV.size(); i++)
		{
			/* Steigung berechnen */
			float Gradiant = (_HiddenNeuronsV[i]->getPosition().y - _InputNeuronsV[c]->getPosition().y) / (_HiddenNeuronsV[i]->getPosition().x - _InputNeuronsV[c]->getPosition().x);
			float Radiant = atan(Gradiant);
			float Degree = (360.0f / (2.0f * 3.14f)) * Radiant;
			float Distance = sqrt(pow(_HiddenNeuronsV[i]->getPosition().y - _InputNeuronsV[c]->getPosition().y, 2) + pow(_HiddenNeuronsV[i]->getPosition().x - _InputNeuronsV[c]->getPosition().x, 2));

			_ConnectionsV.push_back(new sf::RectangleShape);
			_ConnectionsV[_ConnectionsV.size() - 1]->setPosition(_InputNeuronsV[c]->getPosition());
			_ConnectionsV[_ConnectionsV.size() - 1]->setSize(sf::Vector2f(Distance, 1));
			_ConnectionsV[_ConnectionsV.size() - 1]->setRotation(Degree);
			_ConnectionsV[_ConnectionsV.size() - 1]->setFillColor(sf::Color(0, 255, 0));
		}
	}

	for (unsigned int c = 0; c < _HiddenNeuronsV.size(); c++)
	{
		for (unsigned int i = 0; i < _OutputNeuronsV.size(); i++)
		{
			/* Steigung berechnen */
			float Gradiant = (_OutputNeuronsV[i]->getPosition().y - _HiddenNeuronsV[c]->getPosition().y) / (_OutputNeuronsV[i]->getPosition().x - _HiddenNeuronsV[c]->getPosition().x);
			float Radiant = atan(Gradiant);
			float Degree = (360.0f / (2.0f * 3.14f)) * Radiant;
			float Distance = sqrt(pow(_OutputNeuronsV[i]->getPosition().y - _HiddenNeuronsV[c]->getPosition().y, 2) + pow(_OutputNeuronsV[i]->getPosition().x - _HiddenNeuronsV[c]->getPosition().x, 2));

			_ConnectionsV.push_back(new sf::RectangleShape);
			_ConnectionsV[_ConnectionsV.size() - 1]->setPosition(_HiddenNeuronsV[c]->getPosition());
			_ConnectionsV[_ConnectionsV.size() - 1]->setSize(sf::Vector2f(Distance, 1));
			_ConnectionsV[_ConnectionsV.size() - 1]->setRotation(Degree);
			_ConnectionsV[_ConnectionsV.size() - 1]->setFillColor(sf::Color(0, 255, 0));
		}
	}
}

void App::Trainer(float Rotation)
{
	for (unsigned int c = 0; c < _Map.size(); c++)
	{
		if (_Car.getGlobalBounds().intersects(_Map[c]->getGlobalBounds()))
		{
			if (_Balanced == true)
			{
				/* Wenn die Bestleistung übertroffen wurde -> speichern */
				if (_CurrentDistance > _BestDistance)
				{
					_BestDistance = _CurrentDistance;
					std::cout << "Best distance: " << _BestDistance << "! Safing..." << std::endl;
					for (unsigned int c = 0; c < _Connections.size(); c++)
					{
						_Connections[c]->Safe();
					}
				}

				/* Wenn die Bestleistung nicht erreicht wurde -> restoren*/
				if (_CurrentDistance <= _BestDistance)
				{
					std::cout << "Bad evolution! Jumping back to the latest safe point! Restoring..." << std::endl;
					for (unsigned int c = 0; c < _Connections.size(); c++)
					{
						_Connections[c]->Restore();
					}
				}

				/* Versuche Netz zu verbessern */
				for (unsigned int c = 0; c < _Connections.size(); c++)
				{
					_Connections[c]->Mutate(20);
				}
			}

			_CurrentDistance = 0;
			this->ResetCar();
			return;
		}
	}
}