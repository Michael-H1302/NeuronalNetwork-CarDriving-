#pragma once
#include <iostream>

#include "..\Neuron.h"

class InputNeuron : public Neuron
{
	public:

		void SetValue(float NewValue) override;
		float GetValue() override;


	private:

		float _Value;

};