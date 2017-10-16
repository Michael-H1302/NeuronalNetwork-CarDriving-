#pragma once
#include <iostream>

#include "..\Neuron.h"

class OutputNeuron : public Neuron
{
	public:

		void SetValue(float NewValue) override;
		float GetValue() override;

	private:

		float _Value;

};