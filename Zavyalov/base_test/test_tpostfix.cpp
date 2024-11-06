#include "postfix.h"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
  ASSERT_NO_THROW(TPostfix p);
}

TEST(TPostfix, correct_expression_is_correct) {
	TPostfix postfix("(a + b) * ( c + d)");
	try {
		postfix.ToPostfix();
	}
	catch (string s) {
		cout << s << '\n';
	}
	ASSERT_NO_THROW(postfix.ToPostfix(););
}

TEST(TPostfix, incorrect_sequence_of_parentheses_is_an_error) {
	TPostfix postfix("(a + b) * ) c + d(");
	try {
		postfix.ToPostfix();
	}
	catch (string s) {
		cout << s << '\n';
	}
	ASSERT_ANY_THROW(postfix.ToPostfix(););
}

TEST(TPostfix, two_operators_in_a_row_is_an_error) {
	TPostfix postfix("(a + b) */ ( c + d )");
	try {
		postfix.ToPostfix();
	}
	catch (string s) {
		cout << s << '\n';
	}
	ASSERT_ANY_THROW(postfix.ToPostfix(););
}

TEST(TPostfix, operation_after_opening_parenthesis_is_an_error) {
	TPostfix postfix("(a + b) * (* c + d )");
	try {
		postfix.ToPostfix();
	}
	catch (string s) {
		cout << s << '\n';
	}
	ASSERT_ANY_THROW(postfix.ToPostfix(););
}

TEST(TPostfix, calculation_check) {
	TPostfix postfix("(a + b * c) * (b / d - g)");
	postfix.ToPostfix();
	map<char, double> ops;
	ops['a'] = 12.8;
	ops['b'] = 534.64;
	ops['c'] = 756.65;
	ops['d'] = 53.365;
	ops['g'] = 2.0;
	double res = postfix.Calculate(ops);
	double ans = 3.24389 * 1e6;
	ASSERT_TRUE(fabs(res - ans) <= 1);
}

TEST(TPostfix, get_infix_works_properly) {
	TPostfix postfix("(a + b * c) * (b / d - g)");
	postfix.ToPostfix();
	map<char, double> ops;
	ops['a'] = 12.8;
	ops['b'] = 534.64;
	ops['c'] = 756.65;
	ops['d'] = 53.365;
	ops['g'] = 2.0;
	double res = postfix.Calculate(ops);
	string s = postfix.GetInfix();
	ASSERT_TRUE("(a+b*c)*(b/d-g)" == s);
}

TEST(TPostfix, get_postfix_works_properly) {
	TPostfix postfix("(a + b * c) * (b / d - g)");
	postfix.ToPostfix();
	map<char, double> ops;
	ops['a'] = 12.8;
	ops['b'] = 534.64;
	ops['c'] = 756.65;
	ops['d'] = 53.365;
	ops['g'] = 2.0;
	double res = postfix.Calculate(ops);
	string s = postfix.GetPostfix();
	ASSERT_TRUE("abc*+bd/g-*" == s);
}

TEST(TPostfix, infix_change_works_properly) {
	TPostfix postfix("(a + b * c) * (b / d - g) + (a + b * c) * (b / d - g) * (a + b * c) * (b / d - g) / (a + b * c) * (b / d - g)");
	postfix.ToPostfix();
	postfix.change("(a + b * c) * (b / d - g)");
	map<char, double> ops;
	ops['a'] = 12.8;
	ops['b'] = 534.64;
	ops['c'] = 756.65;
	ops['d'] = 53.365;
	ops['g'] = 2.0;
	double res = postfix.Calculate(ops);
	double ans = 3.24389 * 1e6;
	ASSERT_TRUE(fabs(res - ans) <= 1);
}

TEST(TPostfix, get_operands_works_properly) {
	TPostfix postfix("(a + b * c) * (b / d - g) + (a + b * c) * (b / d - g) * (a + b * c) * (b / d - g) / (a + b * c) * (b / d - g)");
	postfix.ToPostfix();
	vector<char> res = postfix.GetOperands();
	vector<char> ops = { 'a','b','c','d','g' };
	ASSERT_TRUE(ops == res);
}
