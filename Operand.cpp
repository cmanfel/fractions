#include "stdafx.h"
#include "Operand.h"

using namespace std;

Error Operand::error;

Operand::Operand() : whole(0), numerator(0), denominator(1), operation('+') 
{
};

Operand::Operand(char* arg, bool expectOperator) : whole(0), numerator(0), denominator(1), operation(0)
{
	unsigned int divOffset = 0;
	unsigned int wholeOffset = 0;
	unsigned int len = strlen(arg);

	for (unsigned int i = 0; i < len; i++)
	{
		if (arg[i] == '_')
		{
			if (wholeOffset == 0)
			{
				wholeOffset = i;
				arg[i] = 0;
			}
			else
			{
				error.setError(multiple_under);
				return;
			}
		}
		else if (arg[i] == '/')
		{
			if (divOffset == 0)
			{
				divOffset = i;
				arg[i] = 0;
			}
			else
			{
				error.setError(multiple_div);
				return;
			}
		}
	}

	if (wholeOffset != 0)
	{
		if (divOffset == 0)
		{
			Operand::error.setError(bad_number);
			return;
		}
		if (!isNum(arg)) return;
		whole = atoi(arg);
		wholeOffset++;
		
	}

	if (divOffset != 0)
	{
		if (!isNum(arg + wholeOffset)) return;
		if (!isNum(arg + divOffset + 1)) return;
		numerator = atoi(arg + wholeOffset);
		denominator = atoi(arg + divOffset + 1);
	}


	simplify();
	toPure();
}

void Operand::multiply(const Operand& operand)
{
	numerator *= operand.numerator;
	denominator *= operand.denominator;
}

void Operand::divide(const Operand& operand)
{
	numerator *= operand.denominator;
	denominator *= operand.numerator;
}

void Operand::add(const Operand& operand)
{
	numerator = numerator * operand.denominator + operand.numerator * denominator;
	denominator *= operand.denominator;
	simplify();
}

void Operand::subtract(const Operand& operand)
{
	numerator = numerator * operand.denominator - operand.numerator * denominator;
	denominator *= operand.denominator;
	simplify();
}

void Operand::doOperation(const Operand& operand)
{
	switch (operation)
	{
	case '-': subtract(operand); break;
	case '+': add(operand); break;
	case '*': multiply(operand); break;
	case '/': divide(operand); break;
	}
}

void Operand::print()
{
	cout << endl << "whole: " << whole << endl;
	cout << "numerator: " << numerator << endl;
	cout << "denominator: " << denominator << endl;
}

void Operand::mix()
{
	if (denominator > numerator)
	{
		return;
	}
	whole = numerator / denominator;
	numerator = numerator % denominator;
}

void Operand::simplify()
{
	int negCount = (whole < 0) + (denominator < 0) + (numerator < 0);
	switch (negCount)
	{
	case 1:
		if (whole > 0)
		{
			whole *= -1;
			numerator = abs(numerator);
			denominator = abs(denominator);
		}
		break;
	case 2:
		numerator = abs(numerator);
		denominator = abs(denominator);
		whole = abs(whole);
		break;
	case 3:
		whole *= -1;
		numerator = abs(numerator);
		denominator = abs(denominator);
		break;
	}
	int minVal = min(abs(numerator), abs(denominator));
	for (int i = minVal; i > 1; i--)
	{
		if ((numerator % i == 0) && (denominator % i == 0))
		{
			numerator /= i;
			denominator /= i;
		}
	}
}

void Operand::setOperation(char* str)
{
	if (strlen(str) > 1)
	{
		error.setError(format_operator);
		return;
	}
	switch (str[0])
	{
	case '+':
	case '-':
	case '*':
	case '/':
		operation = str[0];
		break;
	default:
		error.setError(format_operator);
		break;
	}
}

void Operand::toPure() {
	if (whole != 0)
	{
		numerator += whole * denominator;
		whole = 0;
	}
}

bool Operand::isNum(char* str)
{
	int len = strlen(str);
	for (int i = 0; i < len; i++)
	{
		if (str[i] == '-' || ((str[i] >= '0') && (str[i] <= '9')))
		{
			continue;
		}
		error.setError(bad_number);
		return false;
	}

	return true;
}