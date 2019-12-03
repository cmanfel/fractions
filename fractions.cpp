// fractions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "expression.h"
#include "test.h"

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		test _test;
		_test.run();
		return 0;
	}

	Expression exp(argc, argv);
	exp.printResult();

	return 0;
}

