//--------------------------------------------------------------------
//
//   delimiters.cpp
//
//--------------------------------------------------------------------

#include <iostream>
#include <config.h>
#if LAB6_TEST1
#   include "StackLinked.cpp"
#else
#   include "StackArray.cpp"
#endif

//--------------------------------------------------------------------

bool delimitersOk ( const string &expression );
char openBracket(char c); //helper function

//--------------------------------------------------------------------

int main()
{
	string inputLine;            // Input line
	char   ch;                   // Holding pen for input chars

	cout << "This program checks for properly matched delimiters."
		 << endl;

	cout << "Running test cases..." << endl;
	string testCases[] = {"[{[}]", "(f(b)-(c+d))/2", "(f(b)-(c+2)/2", "(", "{{}}()[()]"};
	for (auto& s : testCases)
	{
		cout << s << " | ";
		if ( delimitersOk (s) )
			cout << "Valid" << endl;
		else
			cout << "Invalid" << endl;
	}

	while( cin )
	{
		cout << "Enter delimited expression (<EOF> to quit) : "
			 << endl;

		// Read in one line
		inputLine = "";
		cin.get(ch);
		while( cin && ch != '\n' )
		{
			inputLine = inputLine + ch;
			cin.get(ch);
		}

		if( ! cin )              // Reached EOF: stop processing
			break;

		if ( delimitersOk (inputLine) )
			cout << "Valid" << endl;
		else
			cout << "Invalid" << endl;
	}

	return 0;
}

//--------------------------------------------------------------------
// delimitersOk: the function that students must implement for
//    Programming Exercise 3.
// Note: we used the term "braces" to describe '[' and ']'. It would
//    have been better to use the term "brackets". The program can be
//    easily modified to process any set of matching delimiters.
//--------------------------------------------------------------------

// Insert your delimitersOk function below
bool delimitersOk ( const string &expression )
{
	//test cases:
	// [{[}]			X
	// (f(b)-(c+d))/2   O
	// (f(b)-(c+2)/2	X
	// (				X
	// {{}}()[()]		O
	#if !LAB6_TEST1
		StackArray<char> delimiters;
	#else
		StackLinked<char> delimiters;
	#endif
	for (auto& c : expression)
	{
		switch (c) {
			case '[': case '{': case '(':
				if (delimiters.isFull()) {
					cout << "Stack full, cannot process further" << endl;
					return false;
				}
				delimiters.push(c);
			break;

			case ']': case '}': case ')':
				if (delimiters.isEmpty()) return false; //improper closing is not ok
				if (openBracket(c) != delimiters.pop()) return false; //closing bracket should be the most recent in the stack
				//delimiters.pop();
			break;
		}
	}
	if (!delimiters.isEmpty()) return false;
	return true;
}

char openBracket(char c)
{
	switch (c) {
		case ']':
			c = '[';
		break;

		case '}':
			c = '{';
		break;

		case ')':
			c = '(';
		break;
	}
	return c;
}
