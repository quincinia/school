#include <sstream>
#include <cctype>
#include <cmath>
#if !LAB6_TEST1
#  include "StackArray.cpp"
#else
#  include "StackLinked.cpp"
#endif

//test expressions
// 5			  = 5
// 3 4 + 5 2 / * 2 ^  = 17.5^2 = 306.25
// 1 +			  = Insufficient operands
// 5 5			  = Incomplete expression
// 5 0 /		  = Division by zero
void postfix(stringstream&, Stack<float>*) throw (invalid_argument);
int main()
{
	string input;
	string testCases[] = {"5", "3 4 + 5 2 / * 2 ^", "1 +", "5 5", "5 0 /"};
	#if !LAB6_TEST1
		Stack<float>* calc = new StackArray<float>();
	#else
		Stack<float>* calc = new StackLinked<float>();
	#endif
	float result;
	stringstream parsing;
	bool error;

	cout << "Running test cases..." << endl;
	for (auto& s : testCases) {
		cout << "Operation " << s << " = ";
		parsing.str(s);
		try {
			postfix(parsing, calc);
		} catch (const exception& e) {
			cerr << "Error: " << e.what() << endl;
			parsing.clear();
			calc->clear();
			continue;
		}
		result = calc->pop();
		cout << result << endl;
	}

	parsing.clear();
	calc->clear();
	cout << "Enter expression: ";
	do {
		error = false;
		getline(cin, input);
		parsing.str(input);
		try {
			postfix(parsing, calc);
		} catch (const exception& e) {
			cerr << "Error: " << e.what() << endl;
			cerr << "Please enter expression again" << endl;
			error = true;
			parsing.clear();
			calc->clear();
		}

	} while (error);
	result = calc->pop();
	cout << "Expression returns: " << result << endl;
	delete calc;
}

void postfix(stringstream& stream, Stack<float>* stack) throw (invalid_argument)
{
	float a, b;
	string parser;
	while (stream.good()) {
		stream >> parser;

			if (isdigit(parser[0])) { //if character is a number
				try {
					stack->push(stof(parser));
				} catch (logic_error) {
					throw invalid_argument("Stack full, cannot process further");
				}

			} else if (parser.find_first_of("+-*/^") != string::npos) {
				try {
					b = stack->pop();
					a = stack->pop();
				} catch (logic_error) {
					throw invalid_argument("Insufficient operands");
				}
				switch (parser[0]) {
					case '+':
						stack->push(a + b);
					break;

					case '-':
						stack->push(a - b);
					break;

					case '*':
						stack->push(a * b);
					break;

					case '/':
						if (b == 0.f) throw invalid_argument("Division by zero");
						stack->push(a / b);
					break;

					case '^':
						//theres no way he expects us to implement fractional exponents
						stack->push(pow(a, b));
					break;
				}
			}
		parser = "";
	}

	if (!stack->hasOne()) throw invalid_argument("Incomplete expression");
	stream.clear();
}
