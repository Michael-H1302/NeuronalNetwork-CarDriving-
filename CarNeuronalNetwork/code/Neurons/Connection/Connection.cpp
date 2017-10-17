#include "Connection.h"

void Connection::SetNeurons(Neuron *In, Neuron *Out)
{
	_In = In;
	_Out = Out;

	_Weight = static_cast<float>(3.0f / (rand() % 9 + 1));
	if ((rand() % 2) == 0)
	{
		_Weight = -_Weight;
	}

	_LastWeight = _Weight;
}

void Connection::Update()
{
	_Out->SetValue(_In->GetValue() * _Weight);
}

void Connection::Mutate()
{
	_LastWeight = _Weight;

	float Mutation = static_cast<float>(((rand() % 3 + 1) / 10.0f) - 0.2f);

	_Weight = _Weight + Mutation;
}

void Connection::Restore()
{
	_Weight = _LastWeight;
}

float Connection::GetWeight()
{
	return _Weight;
}