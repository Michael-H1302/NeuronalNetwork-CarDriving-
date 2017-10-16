#pragma once

#include <iostream>
#include <ctime>
#include "..\Neuron.h"

class Connection
{
	public:

		void SetNeurons(Neuron* In, Neuron* Out);
		void Update();
		void Mutate();
		void Restore();

	private:

		Neuron *_In, *_Out;
		float _Weight;
		float _LastWeight;

};