#include "stdafx.h"
#include "test.h"
#include "expression.h"

TestData::TestData(string _title, vector<string> _input, string _output):
	title(_title),
	input(_input),
	output(_output)
{
}

test::test()
{
	data.push_back(TestData("Multiply", {"?", "1/2", "*", "3_3/4"}, "= 1_7/8"));
	data.push_back(TestData("Add", { "?", "2_3/8", "+", "9/8" }, "= 3_1/2"));
	data.push_back(TestData("Subtract", { "?", "2_3/8", "-", "9/8" }, "= 1_1/4"));
	data.push_back(TestData("Divide", { "?", "2_4/8", "/", "7/14" }, "= 5"));
	data.push_back(TestData("Priority", { "?", "27/9", "+", "6/12", "*", "4/2", "+", "25/50" }, "= 4_1/2"));
	data.push_back(TestData("Signed", { "?", "2_-3/-8", "+", "9/8" }, "= 3_1/2"));
	data.push_back(TestData("Signed 2", { "?", "2_3/8", "+", "9/-8" }, "= 1_1/4"));
	data.push_back(TestData("No Question", { "e", "2_4/8", "/", "7/14" }, "Error: No question mark"));
	data.push_back(TestData("No Argument", { "?"}, "Error: Not enough arguments"));
	data.push_back(TestData("Multiple underscores", { "?", "27/9", "+", "2_6/12_3/11", "*", "4/2", "+", "25/50" }, "Error: Multiple underscores in single operand in argument 4"));
	data.push_back(TestData("Multiple fractions", { "?", "27/9/3", "+", "2_6/12_3/11", "*", "4/2", "+", "25/50" }, "Error: Multiple fractions in single operand in argument 2"));
	data.push_back(TestData("Invalid operation", { "?", "27/9", "+", "2_6/12", "%", "4/2", "+", "25/50" }, "Error: Invalid operation in argument 5"));
	data.push_back(TestData("Invalid Number", { "?", "27/9", "+", "2_6/12.5", "/", "4/2", "+", "25/50" }, "Error: Invalid number in argument 4"));
	data.push_back(TestData("Invalid Number", { "?", "27/9", "+", "2_6-12", "/", "4/2", "+", "25/50" }, "Error: Invalid number in argument 4"));
}

void test::run()
{
	size_t totalCount = data.size();
	size_t passedCount = 0;
	size_t failedCount = 0;
	for (size_t i = 0; i < data.size(); i++)
	{
		Operand::error.reset();
		TestData test_case = data[i];
		cout << endl << "Test: " << test_case.title.c_str() << endl;
		cout << "Input: ";
		for (size_t j = 0; j < test_case.input.size(); j++)
		{
			cout << test_case.input[j].c_str() << " ";
		}
		cout << endl << "Expected: " << test_case.output.c_str() << endl;
		vector<char*> converted_input;
		converted_input.push_back("");
		for (size_t j = 0; j < test_case.input.size(); j++)
		{
			converted_input.push_back((char*)test_case.input[j].c_str());
		}
		Expression exp((int)converted_input.size(), &converted_input[0]);
		string result = exp.getResultString();
		cout << "Actual result: " << result.c_str() << endl;
		if (result.compare(test_case.output) == 0)
		{
			cout << "Test case passed" << endl;
			passedCount++;
		}
		else
		{
			cout << "Test case failed" << endl;
			failedCount++;
		}
	}

	cout << endl << "Executed: " << totalCount << ", Passed: " << passedCount << ", Failed: " << failedCount << endl;
}
