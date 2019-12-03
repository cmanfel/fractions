#pragma once

#include <string>
#include <vector>

using namespace std;

class TestData 
{
public:
	TestData(string title, vector<string> input, string ouput);
public:
	string title;
	vector<string> input;
	string output;
};

class test
{
public:
	test();
	void run();
private:
	vector<TestData> data;
};

