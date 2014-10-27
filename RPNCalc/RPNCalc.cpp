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
void calculate(std::vector<double> &numbers, char operatorIn);//Carry out the maths

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

	std::vector<double> numbersArray;
	for (int i = 0; i < commandItems.size(); i++)
	{
		if (isdigit(commandItems[i].front()))
		{
			numbersArray.push_back(stod(commandItems[i]));
		}
		else if (strchr("+-*/", commandItems[i].front()))
		{
			if (numbersArray.size() < 2)
			{
				cout << "Can't do that.\n";
				return true;
			}
			//calculate
			calculate(numbersArray, commandItems[i].front());
		}
		else
		{
			cout << "I don't know how to parse that.\n";
			return true;
		}
	}
	commandItems.clear();

	// report
	cout << "Result: " << numbersArray.back() << "\n";

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

void calculate(std::vector<double> &numbers, char operatorIn)
{
	double output = numbers.back();
	numbers.pop_back();

	switch (operatorIn)
	{
	case '+':
		output = output + numbers.back();
		numbers.pop_back();
		break;
	case '-':
		output = output - numbers.back();
		numbers.pop_back();
		break;
	case '*':
		output = output * numbers.back();
		numbers.pop_back();
		break;
	case '/':
		output = output / numbers.back();
		numbers.pop_back();
		break;
	default:
		cout << "Something has gone terribly wrong.\n";
		break;
	}

	numbers.push_back(output);
}