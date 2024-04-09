//Willem Wilcox, CSC 245, Dr. Digh, Mercer University, 10/15/23
#include <iostream>
#include <string>
#include <cstdlib>
#include "stack.h"
#include "dsexceptions.h"

using namespace std;

void processInput(string input, Stack<int> & dcStack);
string digitParsing(const string & input);
string operatorParsing(const string & op);
void operatorCheck(string op, Stack<int> & dcStack);
void integerArithmetic(char sym, Stack<int> & dcStack);
int getResult(int op1, int op2, char op);
bool isOperatorChar(char op);

// InvalidOperator class, for exception throw when an invalid operator is recived
class InvalidOperator : public exception {
	virtual const char* what() const throw() {
		return "Invalid operator.";
	}
};

int main() {
	Stack<int> dcStack;
	string input;

	// while loop until ctrl+d is used
	while (!cin.eof()) {
		cin >> input;
		// after cin check what was stored
		processInput(input, dcStack);
	}

	return 0;
}

// processInput function, checks if given input from cin is a operand or operator;
// pushes operators to the stack, pushes operators to a void function, operatorCheck
void processInput(string input, Stack<int> & dcStack) {
	// Pre: input is user input and within capacity of a string 
	// Post: performs action or throws error
	//		 Actions include: adding a number to the stack, 
	//						arithmetic functions (add, sub, mul, div, mod)
	//						print top, pop top, print stack, clear stack, reverse top two, duplicate top two

	int num = 0;
	string remainder;

	try {
		// while loop ends when input is parsed,
		// input size decreases as parsed parts are removed
		while (input.length() > 0) {
			if(isdigit(input[0]) || input[0] == '_') {
				remainder = digitParsing(input);
			}
			else {
				remainder = operatorParsing(input);
			}
		
			// conditional checking if input is a num (or _ for neg input) or operand, 
			// operands are pushed to dcStack, operators are sent to
			// operatorCheck function to perform calc functions
			if (isdigit(input[0]) || ((input[0] == '_') && isdigit(input[1]))) {
				if (input[0] == '_') {
					input[0] = '-';
				} 
				num = atoi(input.c_str());
				dcStack.push(num);
			}
			else {
				// Input is not digit, try operatorCheck
				operatorCheck(input, dcStack);
				input = remainder;
			}
		}
	} catch (exception &e) {
		cout << "Invalid input. Try Again." << endl;
	}
}

// Returns substring without the number
string digitParsing(const string & input) {
	// Pre: string input contains digit or _
	// Post: returns substring without digit included
	int index = 0;
	// chops off remaining string after first digit
	for (int i = 0; i < input.length(); i++) {
		// checks if input is digit, then chops after that index
		if (isdigit(input[i]) || (input[i] == '_')){
			index = i;
		}
	}
	return input.substr(index +1);
}

// Returns substring without the operator
string operatorParsing(const string & op) {
	// Pre: string input contains p,n,f, or r
	// Post: returns substring without digit included
	int index = 0;
	// chops off remaining string after first digit
	for (int i = 0; i < op.length(); i++) {
		// checks if it is a operator, then chops after that index
		if ((op[i] == 'p') || (op[i] == 'P') ||
			(op[i] == 'n') || (op[i] == 'N') ||
			(op[i] == 'f') || (op[i] == 'F') || 
			(op[i] == 'r') || (op[i] == 'R') ||
			(isOperatorChar(op[i]))) {
			index = i;
		}
	}	
	return op.substr(index + 1);
}

// operatorCheck function, checks what operator given input is and preforms corresponding
// operation (using integerArithmetic)
void operatorCheck(string input, Stack<int> & dcStack) {
	// Pre: input contains an operator, has built in extra check for any numbers found
	// Post: Performs all calc actions
	try {
		string number_found = "";

		for (int k = 0; k < input.length();k++) {
			// checks
			char op = input.at(k);
			if (isdigit(op) || op == '_'){
				if (op == '_') {
					op = '-';
				} 
				number_found += op;
			} 
			else {
				//incase extra numbers are between commands
				if (number_found != "") {
					int num = atoi(number_found.c_str());
					dcStack.push(num);
				}

				if (op == 'p' || op == 'P') {
					// print top of dcStack
					cout << dcStack.top() << endl;
				}
				else if (op == 'n' || op == 'N') {
					// print then pop top
					cout << dcStack.topAndPop();
				}
				else if (op == 'f' || op == 'F') {
					Stack<int> tempStack = dcStack;
					// while tempStack isn't empty print and pop all values
					while (!tempStack.isEmpty()) {
						int temp = tempStack.topAndPop();
						cout << temp << " ";
					}
           
					//cout << endl;
				}
				else if (op == 'c' || op == 'C') {
					// clear dcStack 
					dcStack.makeEmpty();
				}
				else if (op == 'd' || op == 'D') {
					// duplicate top value in dcStack
					int top = dcStack.top();
					dcStack.push(top);
				}
				else if (op == 'r' || op == 'R') {
					// switch top two values in dcStack
					int t1 = dcStack.topAndPop();
					int t2 = dcStack.topAndPop();
					dcStack.push(t1);
					dcStack.push(t2);
				}
				else if (isOperatorChar(op)){
					// if numerical operator, preforms integer arithmetic
					// base case
					integerArithmetic(op, dcStack);
				}
		  	}	
   		}
	} 
	catch (const Underflow &e) {
		cout << "Illegal Pop -- Stack is Empty." << endl;
	} 
	catch (const Overflow &e) {
		cout << "Stack overflow error." << endl;
	} 
	catch (const InvalidOperator &e) {
		cout << "Invalid operator." << endl;
	}
}

// integerArithmetic function, preforms numerical operation between top two operands 
// in dcStack then store result in top of dcStack
void integerArithmetic(char sym, Stack<int> & dcStack) {
	//Pre: dcStack is initialized
	//Post: if sym is an operator, attempts getResult

	// dcStack underflow check
	if (dcStack.isEmpty()){
		throw Underflow();
	} 
	else {
		// take top integer and store as second operand
		int op2 = dcStack.topAndPop();
		
		// dcStack underflow check
		if (dcStack.isEmpty()) {
			// push first value back before quit
			dcStack.push(op2);
			throw Underflow();
		} 
		else {
			// take second to top integer and store as first operand
			int op1 = dcStack.top();
			dcStack.pop();

			// calculate and store result in dcStack
			int result = getResult(op1, op2, sym);
			dcStack.push(result);
		}
	}
}

// getResult function, calculate and return the final result for a numerical 
int getResult(int valueOne, int valueTwo, char op) {
	//Pre: char op passes isOperatorChar
	//Post: returns result or throws error


	// switch for numerical calcualtions
	switch (op) {
		// add
		case '+': return valueOne + valueTwo; break;
		// subtract
		case '-': return valueOne - valueTwo; break;
		// multiply
		case '*': return valueOne * valueTwo; break;
		//divide
		case '/': {
			// error handling for division by 0
			if (valueTwo == 0) {
				throw DivisionByZero();
			}
			return valueOne / valueTwo;
		}
		// remiander
		case '%': {
			if (valueTwo == 0) {
				throw DivisionByZero();
			}
			return valueOne % valueTwo;
		}
		// base case, invalid operator
		default: throw InvalidOperator();
	}
}

// helper method, if int operator present returns true
bool isOperatorChar(char op) {
	//Pre: op is a char
	//Post: returns true if +, -, *, /, %
	if ((op == '+') || 
		(op == '-') || 
		(op == '*') || 
		(op == '/') ||
		(op == '%')) {
		
		return true;
	}

	else return false;
}