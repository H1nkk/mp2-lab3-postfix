#ifndef __POSTFIX_H__
#define __POSTFIX_H__


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
	vector<char> lexems; // char -> string
	map<char, int> priority;
	map<char, double> operands;


	void Parse() {
		despace();
		check();
		for (char c : infix) {
			lexems.push_back(c);
		}
	}

public:
	TPostfix(string infx = "") : infix(infx) {
		priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };
	}
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	
	void change(string new_inf) {
		infix = new_inf;
		ToPostfix();
	}
	void despace();
	void check();
	string ToPostfix();

	vector<char> GetOperands() const {
		vector<char> op;
		for (const auto& item : operands)
			op.push_back(item.first); // ещё операндами мб консты
		return op;
	}

	double Calculate(const map<char, double>& values); // Ввод переменных, вычисление по постфиксной форме

	
};

#endif
