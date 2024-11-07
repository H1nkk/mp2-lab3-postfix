#pragma once

#include "stack.h"
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <set>

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	vector<char> lexems;
	map<char, int> priority;
	map<char, double> operands;

	void check();

	void despace();

	void Parse();

public:
	TPostfix(string infx = "") : infix(infx) {
		priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };
	}

	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	
	void change(string new_inf);
	
	string ToPostfix();

	vector<char> GetOperands() const;

	double Calculate(const map<char, double>& values);
	
};

