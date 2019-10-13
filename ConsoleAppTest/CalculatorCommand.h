#pragma once
class CalculatorCommand
{
public:
	CalculatorCommand();
	virtual ~CalculatorCommand();
	virtual float execute(float initialValue, float calculationValue) = 0;
};




class CalculatorAssign : public CalculatorCommand
{
public:
	float execute(float initialValue, float calculationValue);
};


class CalculatorAdd : public CalculatorCommand
{
public:
	float execute(float initialValue, float calculationValue);
};


class CalculatorHelp : public CalculatorCommand
{
public:
	float execute(float initialValue, float calculationValue);
};