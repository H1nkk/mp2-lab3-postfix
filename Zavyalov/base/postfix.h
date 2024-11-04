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
	vector<char> lexems; // char -> string
	map<char, int> priority;
	map<char, double> operands;

	void Parse() {
		check();
		despace();
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
	void despace() {
		string tmp;
		for (char x : infix) {
			if (x != ' ')
				tmp += x;
		}
		infix = tmp;
	}
	void check() {
		if (infix == "") throw "Cannot calculate empty expression";

		set<char> operations = { '+', '-', '/', '*' };
		int parenthesis_count = 0;

		char prev = '$';
		for (int i = 0; i < infix.size(); i++) {

			char cur = infix[i];
			if (cur == ' ') continue;

			// check if every symbol is a letter or an operation sign
			bool ok = false;
			ok |= ('a' <= cur && cur <= 'z');
			ok |= ('A' <= cur && cur <= 'Z');
			ok |= cur == '+';
			ok |= cur == '-';
			ok |= cur == '/';
			ok |= cur == '*';
			ok |= cur == '(';
			ok |= cur == ')';
			// ok |= ('0' <= cur && cur <= '9'); // для констант, пока не реализовал
			// ok |= cur == '.'; //  для floating point констант, пока не реализовал
			if (!ok) {
				string alert = "Invalid symbol at index ";
				alert += to_string(i);
				throw alert;
			}

			// check if opening and closing parenthesis match
			if (cur == '(') parenthesis_count++;
			if (cur == ')') parenthesis_count--;
			if (parenthesis_count < 0) {
				string alert = "Parenthesis mismatch staring from index ";
				alert += to_string(i);
				throw alert;
			}

			// check if no empty parenthesis
			if (cur == ')') {
				if (prev == '(') {
					string alert = "Empty parenthesis at index ";
					alert += to_string(i - 1);
					throw alert;
				}
			}

			// check if no sequential operation signs БЕЗ УЧЕТА УНАРНЫХ +-
			if (operations.count(cur)) {
				if (prev == '(') { // ПОКА БЕЗ УНАРНЫХ +-
					string alert = "Operation ";
					alert += cur;
					alert += " right after opening parenthesis is not allowed. (At index ";
					alert += to_string(i);
					alert += ")";
					throw alert;
				}
				if (operations.count(prev)) {
					string alert = "Sequential operation signs at index ";
					alert += to_string(i);
					throw alert;
				}
			}
			prev = cur;
		}

		if (parenthesis_count != 0) {
			throw "Mismatch of opening and closing brackets";
		}
	}
	string ToPostfix() {
		Parse();
		TStack<char> st(100);
		char stackItem;
		for (char item : lexems) {
			switch (item)
			{
			case '(':
				st.push(item);
				break;
			case ')':
				stackItem = st.pop();
				while (stackItem != '(') {
					postfix += stackItem;
					stackItem = st.pop();
				}
				break;
			case '+': case '-': case '*': case'/':
				while (!st.empty()) {
					stackItem = st.pop();
					if (priority[item] <= priority[stackItem])
						postfix += stackItem;
					else {
						st.push(stackItem);
						break;
					}
				}
				st.push(item);
				break;
			default:
				operands[item] = 0.0;
				postfix += item;
				break;
			}
		}
		while (!st.empty()) {
			stackItem = st.pop();
			postfix += stackItem;
		}
		return postfix;
	}

	vector<char> GetOperands() const {
		vector<char> op;
		for (const auto& item : operands)
			op.push_back(item.first); // ещё операндами мб консты
		return op;
	}

	double Calculate(const map<char, double>& values) {
		for (auto& val : values) {
			try {
				operands.at(val.first) = val.second;
			}
			catch (out_of_range& e) {}
		}
		TStack<double> st(100);
		double leftOperand, rightOperand;
		for (char lexem : postfix) {
			switch (lexem) {
			case '+':
				rightOperand = st.pop();
				leftOperand = st.pop();
				st.push(leftOperand + rightOperand);
				break;
			case '-':
				rightOperand = st.pop();
				leftOperand = st.pop();
				st.push(leftOperand - rightOperand);
				break;
			case '*':
				rightOperand = st.pop();
				leftOperand = st.pop();
				st.push(leftOperand * rightOperand);
				break;
			case '/':
				rightOperand = st.pop();
				leftOperand = st.pop();
				st.push(leftOperand / rightOperand);
				break;
			default:
				st.push(operands[lexem]);
				break;
			}
		}
		return st.pop();
	}
	
};

