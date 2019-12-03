#pragma once

#include "error.h"

class Operand
{
public:
	Operand();
	Operand(char* arg, bool expectOperator);

	void multiply(const Operand& operand);
	void divide(const Operand& operand);
	void add(const Operand& operand);
	void subtract(const Operand& operand);
	void doOperation(const Operand& operand);
	void print();
	void mix();
	void simplify();
	void setOperation(char* str);

private:
	void toPure();
	bool isNum(char* str);
public:
	// Data
	int whole;
	int numerator;
	int denominator;
	char operation;
	static Error error;
};