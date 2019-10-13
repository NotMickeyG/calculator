#include "stdafx.h"
#include "CalculatorCommand.h"


CalculatorCommand::CalculatorCommand()
{
}


CalculatorCommand::~CalculatorCommand()
{
}




float CalculatorAssign::execute(float initialValue, float calculationValue)
{
	float answer = initialValue;
	// output?
	return answer;
}


float CalculatorAdd::execute(float initialValue, float calculationValue)
{
	float answer = initialValue + calculationValue;
	// output?
	return answer;
}


float CalculatorHelp::execute(float initialValue, float calculationValue)
{
	float answer = initialValue;
	// output help
	return answer;
}