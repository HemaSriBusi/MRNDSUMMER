#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

bool checkstr(char *s) {
	int i = 0;
	while (s[i] != '\0') {
		if (isalpha(s[i]))
			return true;
		i++;
	}
	return false;
}

int evalExp(char *exp, char *excel[11][11]) {
	stack<int> values;
	stack<char> operatr;
	char  a = 'b';
	int b = 2;
	int c = 3;
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
			int column = exp[i] - 64;
			i++;
			int row = exp[i] - 48;
			char *s = excel[row][column];
			if (checkstr(s)) 
				values.push(evalExp(s, excel));
			else {
				int val = atoi(s);
				values.push(val);
			}
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
	errno_t err;
	FILE *fp;
	char *excel[11][11];
	excel[0][0] = "0";
	for (int i = 1; i < 11; i++) {
		char *temp = (char *)malloc(sizeof(char) * 3);
		temp[0] = i + 64;
		temp[1] = '\0';
		excel[0][i] = temp;
		//strcpy(excel[0][i], temp);
	}
	for (int i = 1; i < 11; i++) {
		if (i == 10)
			excel[i][0] = "10\0";
		else {
			char *temp = (char *)malloc(sizeof(char) * 3);
			temp[0] = i + 48;
			temp[1] = '\0';
			excel[i][0] = temp;
			//strcpy(excel[i][0], temp);
		}
	}
	for (int i = 1; i < 11; i++) {
		for (int j = 1; j < 11; j++) {
			char *temp = (char *)malloc(sizeof(char) * 3);
			temp = "0\0";
			//strcp(excel[i][j],temp);
			excel[i][j] = temp;
		}
	}

	while (1) {
		printf(">");
		char option[30];
		gets_s(option);
		if (strstr(option, "get")) {
			int column = option[3] - 64;
			int row = option[4] - 48;
			char *val = excel[row][column];
			//printf("%d\n", strlen(val));
			if (checkstr(val)) {
				int value = evalExp(val, excel);
				printf("%d\n", value);
			}
			else
				printf("%s\n", excel[row][column]);
		}
		else if (strstr(option, "set")) {
			int column = option[3] - 64;
			int row = option[4] - 48;
			char *value = (char *)malloc(sizeof(char) * 10);
			int i = 6, j = 0;
			while (option[i] != '\0') {
				value[j] = option[i];
				i++;
				j++;
			}
			value[j] = '\0';
			excel[row][column] = value;
		}
		else if (strstr(option, "print")) {
			for (int i = 0; i < 11; i++) {
				for (int j = 0; j < 11; j++) {
					printf("%s\t", excel[i][j]);
				}
				printf("\n");
			}
		}
		else if (strstr(option, "export")) {
			fp = fopen( "data.csv", "w");
			if (fp != NULL) {
				/*fprintf(fp, "%s", "0");
				fprintf(fp, "%s", ",");
				for (int i = 1; i < 11; i++) {
					fprintf(fp, "%s", excel[0][i]);
					if (i != 10)
						fprintf(fp, "%s", ",");
				}
				fprintf(fp, "%s", "\n");*/
				for (int i = 1; i < 11; i++) {
					//fprintf(fp, "%s", excel[i][0]);
					//fprintf(fp, "%s", ",");
					for (int j = 1; j < 11; j++) {
						fprintf(fp, "%s", excel[i][j]);
						if ( j != 10)
							fprintf(fp, "%s", ",");
					}
					fprintf(fp, "%s", "\n");
				}
			}
			else
				printf("Unsuccessful");
			fclose(fp);
		}
		else if (strstr(option, "import")) {
			fp = fopen("data.csv", "r");
			char c[128];
			FILE *fp;
			fp = fopen("data.csv", "r");
			if (fp == NULL){
				printf("error");
			}
			if (fp != NULL){
				int i = 1;
				while (fscanf(fp, "%[^\n]\n", c) != EOF){
					int j = 1;
					printf(c);
					printf("\n");
					char *token = (char *)malloc(sizeof(char) * 20);
					token = strtok(c, ",");
					while (token != NULL) {
						char *temp = (char *)malloc(sizeof(char) * 10);
						int l = 0, k = 0;
						while (token[k] != '\0') {
							temp[l] = token[k];
							l++;
							k++;
						}
						temp[l] = '\0';
						excel[i][j] = temp;
						token = strtok(NULL, ",");
						j++;
					}
					i++;
				}
			}
			else
				printf("Unsuccessful");
			fclose(fp);
			fclose(fp);
		}
		else if ( strstr(option,"exit") )
			exit(0);
	}
}