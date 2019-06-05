#include "stdafx.h"
#include <iostream>
#include <stack>
#include <ctype.h>

using namespace std;

int solveOp(char op, int op1, int op2) {
	if (op == '*')
		return op1 * op2;
	else if (op == '+')
		return op1 + op2;
	else if (op == '-')
		return op1 - op2;
	else if (op == '/')
		return op1 / op2;
	else
		return op1 % op2;
}

int isprecedence(char op) {
	if (op == '^')
		return 3;
	else if (op == '%' || op == '/')
		return 2;
	else if (op == '+' || op == '-')
		return 1;
	return 0;
}

int evalExp(char *exp) {
	stack<int> values;
	stack<char> operatr;
	for (int i = 0; exp[i] != '\0'; i++) {
		if (exp[i] == ' ')
			continue;

		else if (exp[i] == '(')
			operatr.push(exp[i]);

		else if (isdigit(exp[i])) {
			int val = 0;
			while (isdigit(exp[i]) && exp[i] != '\0') {
				val = (val * 10) + (exp[i] - 48);
				i++;
			}
			i--;
			values.push(val);
		}

		else if (exp[i] == ')') {
			while (!operatr.empty() && operatr.top() != '(') {
				char op = operatr.top();
				operatr.pop();
				int op2 = values.top();
				values.pop();
				int op1 = values.top();
				values.pop();
				int val = solveOp(op, op1, op2);
				values.push(val);

			}
			operatr.pop();
		}

		else if (isalpha(exp[i])) {
			int val = exp[i];
			values.push(val);
		}

		else {
			while (!operatr.empty() && (isprecedence(operatr.top()) >= isprecedence(exp[i]))) {
				char op = operatr.top();
				operatr.pop();
				int op2 = values.top();
				values.pop();
				int op1 = values.top();
				values.pop();
				int val = solveOp(op, op1, op2);
				values.push(val);
			}
			operatr.push(exp[i]);
		}
	}
	while (!operatr.empty()) {
		char op = operatr.top();
		operatr.pop();
		int op2 = values.top();
		values.pop();
		int op1 = values.top();
		values.pop();
		int val = solveOp(op, op1, op2);
		values.push(val);
	}
	return values.top();
}


int main() {
	char exp[30] = "7/2";
	cout << evalExp(exp) << endl;
	return 0;
}
