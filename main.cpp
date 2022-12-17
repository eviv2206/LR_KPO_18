#include <iostream>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;


typedef enum Tokens
{
	UNDEFINED = 0,
	LATTER_UNDERLINE,
	DIGIT,
}Tokens;


const unsigned int BEGIN_STATE = 1;
const unsigned int REJECT_STATE = 0;

const bool VALID_EXPR_ARR[3] = { false, false, true };

const unsigned int REGULAR_MATRIX[3][3] = {
	{0, 0, 0},
	{0, 2, 0},
	{0, 2, 2}
};


Tokens getToken(char currentChar) {
	Tokens charToken = UNDEFINED;
	if (currentChar == '_' || (currentChar >= 'a' && currentChar <= 'z') || (currentChar >= 'A' && currentChar <= 'Z'))
	{
		charToken = LATTER_UNDERLINE;
	}
	else if (currentChar >= '0' && currentChar <= '9')
	{
		charToken = DIGIT;
	}
	return charToken;
}

void loadIdents(string expr, bool findAll)
{
	string token;
	unsigned int currentState = BEGIN_STATE;
	unsigned int exprState = BEGIN_STATE;
	unsigned exprPoss = 0;
	while (exprPoss < expr.length() - 1)
	{
		token += expr[exprPoss];
		currentState = REGULAR_MATRIX[currentState][getToken(expr[exprPoss])];
		exprState = REGULAR_MATRIX[currentState][getToken(expr[exprPoss + 1])];
		if (token.length() > 0 && VALID_EXPR_ARR[currentState] && !VALID_EXPR_ARR[exprState])
		{
			cout << token << endl;
		}

		if (currentState == REJECT_STATE || exprState == REJECT_STATE)
		{

			exprState = BEGIN_STATE;
			currentState = BEGIN_STATE;
			token.clear();
		}
		exprPoss++;
	}
	exprState = REGULAR_MATRIX[currentState][getToken(expr[exprPoss])];
	if (VALID_EXPR_ARR[exprState])
	{
		token += expr[exprPoss];
	}
	if (VALID_EXPR_ARR[currentState] || VALID_EXPR_ARR[exprState])
	{
		if (findAll)
			cout << token << endl;
		else {
			if (strcmp(token.c_str(), expr.c_str()) == 0)
				cout << "correct" << endl;
			else
				cout << "incorrect" << endl;
		}
	}
	token = "";
}

int main() {
	cout << "input expression" << endl;
	string expr;
	getline(cin, expr);
	cout << "Enter 1 to check for correctence, using other to find all identificators" << endl;
	int ch;
	cin >> ch;
	loadIdents(expr, ch != 1);
	return 0;
}
