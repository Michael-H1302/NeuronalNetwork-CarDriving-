#include "OutputNeuron.h"

void OutputNeuron::SetValue(float NewValue)
{
	_Value = _Value + NewValue;
}

float OutputNeuron::GetValue()
{
	_Value = 1 / (1 + pow(2.71828f, _Value));

	float Return = _Value;
	_Value = 0;

	return Return;
}