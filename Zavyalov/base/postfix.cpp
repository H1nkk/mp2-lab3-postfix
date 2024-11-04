#include "postfix.h"
#include "stack.h"

string TPostfix::ToPostfix()
{
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

double TPostfix::Calculate(const map<char, double>& values)
{
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

void TPostfix::despace() {
	string tmp;
	for (char x : infix) {
		if (x != ' ')
			tmp += x;
	}
	infix = tmp;
}

void TPostfix::check() {
	if (infix == "") throw "Cannot calculate empty expression";

	set<char> operations = { '+', '-', '/', '*' };
	int parenthesis_count = 0;

	char prev = '$';
	for (int i = 0; i < infix.size(); i++) {

		char cur = infix[i];

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
			if (operations.count(prev)) {
				string alert = "Sequential operation signs at index ";
				alert += to_string(i);
				throw alert;
			}
		}
	}

	if (parenthesis_count != 0) {
		throw "Mismatch of opening and closing brackets";
	}
}