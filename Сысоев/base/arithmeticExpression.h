#pragma once
#include "stack.h"
#include "postfix.h"
#include <vector>
#include <map>

class TArithmeticExpression {
	TPostfix postfix;
	vector<char> lexems; // char -> string
	map<char, int> priority;
	map<char, double> operands;

	void Parse() {

	}
	void ToPostfix() {

	}
public:
	TArithmeticExpression(string infx): postfix(infx) {}

	string GetInfix() {
		return postfix.GetInfix();
	}
	
	string GetPostfix() {
		return postfix.GetPostfix();
	}

};
