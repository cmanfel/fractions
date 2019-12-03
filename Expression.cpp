#include "stdafx.h"
#include "Expression.h"

using namespace std;

Expression::Expression(int argc, char *argv[]) : expectOperator(false)
{
	// Basic command line format verifications
	if (argc < 3)
	{
		Operand::error.setError(no_arguments);
		return;
	}

	if (argv[1][0] != '?')
	{
		Operand::error.setError(no_q);
		return;
	}

	for (int i = 2; i < argc; i++)
	{
		Operand::error.setIndex(i);
		if (expectOperator)
		{
			if (strlen(argv[i]) > 1)
			{
				Operand::error.setError(format_operator);
				return;
			}
			else
			{
				back().setOperation(argv[i]);
			}
		}
		else
		{
			Operand op((char*)argv[i], expectOperator);
			addOperand(op);
		}
		if (Operand::error.hasError())
		{
			return;
		}
		expectOperator = !expectOperator;
	}

	do
	{
		result.doOperation(front());
		result.operation = front().operation;
		pop_front();
	} while (!empty());

}

string Expression::getResultString()
{
	if (Operand::error.hasError())
	{
		return Operand::error.getErrorString();
	}

	result.mix();
	result.simplify();
	
	string resultStr = "= ";

	if (result.whole != 0)
	{
		char buffer[128] = { 0 };
		sprintf_s(buffer, "%i", result.whole);
		resultStr.append(buffer);
	}

	if(result.numerator != 0 && result.denominator != 1)
	{ 
		char buffer[128] = { 0 };
		sprintf_s(buffer, "_%i/%i", result.numerator, result.denominator);
		resultStr.append(buffer);
	}

	return resultStr;
}

void Expression::printResult()
{
	cout << endl << getResultString().c_str() << endl;
}

void Expression::addOperand(const Operand& op)
{
	if (empty())
	{
		push_back(op);
	}
	else
	{
		char lastOp = back().operation;
		if (lastOp == '*' || lastOp == '/')
		{
			back().doOperation(op);
			back().operation = 0;
		}
		else
		{
			push_back(op);
		}
	}
}