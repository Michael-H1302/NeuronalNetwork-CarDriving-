#pragma once

class Neuron
{
	public:

		virtual void SetValue(float NewValue) = 0;
		virtual float GetValue() = 0;

	protected:

		float _Value;

};