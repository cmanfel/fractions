#include "stdafx.h"
#include "Error.h"

using namespace std;

Error::Error() : code(success), index(0) 
{
};

bool Error::hasError() 
{ 
	return (code != success); 
};

void Error::setError(_error_code _code) 
{ 
	code = _code; 
};

void Error::setIndex(int _index)
{ 
	index = _index; 
};

void Error::reset()
{
	index = 0;
	code = success;
};

string Error::getErrorString()
{
	char buffer[1024] = { 0 };
	sprintf_s(buffer, "Error: %s", errorMessages[code].c_str());
	string result(buffer);
	if (index != 0)
	{
		char bufferIndex[128] = { 0 };
		sprintf_s(bufferIndex, " in argument %i", index);
		result.append(bufferIndex);
	}

	return result;
}

void Error::print()
{
	cout << endl << getErrorString().c_str() << endl;
}
