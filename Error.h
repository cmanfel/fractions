#pragma once

#include <vector>
#include <string>

using namespace std;

typedef enum error_code { success, no_arguments, no_q, multiple_under, multiple_div, format_operator, bad_number } _error_code;

class Error
{
public:
	Error();
	bool hasError();
	void setError(_error_code _code);
	void setIndex(int _index);;
	string getErrorString();
	void print();
	void reset();

private:
	// Data
	_error_code code;
	int index;
	const vector<string> errorMessages = 
	{ 
		"No Error", 
		"Not enough arguments", 
		"No question mark", 
		"Multiple underscores in single operand", 
		"Multiple fractions in single operand", 
		"Invalid operation", 
		"Invalid number"
	};
};
