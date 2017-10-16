#include "OutputNeuron.h"

void OutputNeuron::SetValue(float NewValue)
{
	_Value = NewValue;
}

float OutputNeuron::GetValue()
{
	return _Value;
}