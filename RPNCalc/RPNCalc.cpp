// RPNCalc.cpp : main project file.
// A reverse Polish notation calculator.
// 2014 EMcG
// In response to a challenge from SPT.
// Probably three hours or so?

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>

using namespace System;
using namespace std;

bool mainLoop();//Do the thing.
void split(std::string stringIn, std::vector<std::string> &arrayOut);//Split an input string into an array, by whitespace.
double calculate(int it, double scratch, std::vector<std::string> &numbers, std::vector<char> &operators);//Carry out the maths

int main(array<System::String ^> ^args)
{
	bool runFlag = true;
	std::string stringIn;

	cout << "This is a reverse Polish notation calculator.\n";

	while (runFlag)
	{
		runFlag = mainLoop();
	}
	return 1;
}

bool mainLoop()
{
	std::string commandIn;

	// prompt
	cout << "Enter command (blank to quit): ";
	getline(cin, commandIn);

	std::vector<std::string> commandItems;
	// parse
	if (!commandIn.length())
	{
		cout << "Quitting\n";
		return false;
	}
	split(commandIn, commandItems);

	std::vector<std::string> numbersArray;
	std::vector<char> operatorsArray;
	for (int i = 0; i < commandItems.size(); i++)
	{
		if (isdigit(commandItems[i].front()))
		{
			numbersArray.push_back(commandItems[i]);
		}
		else if (strchr("+-*/^", commandItems[i].front()))
		{
			operatorsArray.push_back(commandItems[i].front());
		}
		else
		{
			cout << "I don't know how to parse that.\n";
			return true;
		}
	}
	commandItems.clear();

	// basic sanity check
	if (operatorsArray.size() >= numbersArray.size())
	{
		cout << "That is not how mathematics works.\n";
		return true;
	}
	
	double result = stod(numbersArray[0]);
	// calculate
	for (int i = 0; i < operatorsArray.size(); i++)
	{
		result = calculate(i, result, numbersArray, operatorsArray);
	}
	numbersArray.clear();
	operatorsArray.clear();

	// report
	cout << "Result: " << result << "\n";

	return true;
}

void split(std::string stringIn, std::vector<std::string> &arrayOut)
{
	std::string splitStr;
	std::stringstream ss(stringIn);

	while (ss >> splitStr)
	{
		arrayOut.push_back(splitStr);
	}
}

double calculate(int it, double calcSoFar, std::vector<std::string> &numbers, std::vector<char> &operators)
{
	double output;

	switch (operators[it])
	{
	case '+':
		output = calcSoFar + stod(numbers.back());
		numbers.pop_back();
		break;
	case '-':
		output = calcSoFar - stod(numbers.back());
		numbers.pop_back();
		break;
	case '*':
		output = calcSoFar * stod(numbers.back());
		numbers.pop_back();
		break;
	case '/':
		output = calcSoFar / stod(numbers.back());
		numbers.pop_back();
		break;
	case '^':
		for (int i = 1; i < stoi(numbers.back()); i++)
		{
			output = calcSoFar * calcSoFar;
		}
		numbers.pop_back();
		break;
	default:
		cout << "Something has gone terribly wrong.\n";
		break;
	}

	return output;
}