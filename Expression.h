#pragma once

#include <list>
#include <string>

#include "operand.h"

class Expression : public std::list<Operand>
{
public:
	Expression(int argc, char *argv[]);
	void printResult();
	std::string getResultString();

private:
	void addOperand(const Operand& op);

private:
	// Data
	bool expectOperator;
	Operand result;
};


