#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	string expression;
	double res;

	setlocale(LC_ALL, "Russian");
	cout << "Введите арифметическое выражение: ";
	getline(cin, expression);
	expression = "(a + b) * ) c + d(";
	cout << expression << endl;
	TPostfix postfix(expression);
	cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
	postfix.ToPostfix();
	cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
	postfix.check();
	cout << "Введите значения переменных: \n";
	auto ops = postfix.GetOperands();
	map<char, double> mp;
	for (auto x : ops) {
		cout << x << ": ";
		cin >> mp[x];
	}
	res = postfix.Calculate(mp);
	cout << res << endl;

	return 0;
}
