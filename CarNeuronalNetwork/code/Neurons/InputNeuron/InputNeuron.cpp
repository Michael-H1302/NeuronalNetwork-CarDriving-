#include "InputNeuron.h"

void InputNeuron::SetValue(float NewValue)
{
	_Value = NewValue;
}

float InputNeuron::GetValue()
{
	return _Value;
}