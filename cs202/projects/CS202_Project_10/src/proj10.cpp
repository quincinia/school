#include <iostream>
#include <ArrayStack/ArrayStack.hpp>
#include <NodeStack/NodeStack.hpp>
using namespace std;

//This code is my own work. It was written without consulting a tutor or code written by other students.

int main()
{
	{
	cout << "***Testing ArrayStack<int>***" << endl;
	ArrayStack<int> aq1, aq2(3, 5), aq3(aq2);
	aq1 = aq3;
	cout << "Testing ArrayStack top()" << endl;
	cout << "Before: \n" << aq1 << endl;
	aq1.top() = 60;
	cout << "After: \n" << aq1 << endl;
	cout << "Testing ArrayStack push()" << endl;
	aq1.push(5);
	cout << aq1 << endl;
	cout << "Testing ArrayStack pop()" << endl;
	aq1.pop();
	cout << aq1 << endl;

	cout << "Testing ArrayStack size()" << endl;
	cout << "Size: " << aq1.size() << endl;
	cout << aq1 << endl;

	cout << "Testing ArrayStack clear()" << endl;
	aq1.clear();

	cout << "Testing ArrayStack empty()" << endl;
	cout << (aq1.empty() ? "> Stack is empty\n" : "> Stack is not empty\n");

	cout << "\nTesting ArrayStack full()" << endl;
	ArrayStack<int> aqf(1000, 5);
	cout << (aqf.full() ? "> Stack is full\n" : "> Stack is not full\n");


	cout << "\n\n***Testing NodeStack<int>***" << endl;
	NodeStack<int> nq1, nq2(3, 7), nq3(nq2);
	nq1 = nq3;
	cout << "Testing NodeStack top()" << endl;
	cout << "Before: \n" << nq1 << endl;
	nq1.top() = 80;
	cout << "After: \n" << nq1 << endl;
	cout << "Testing NodeStack push()" << endl;
	nq1.push(7);
	cout << nq1 << endl;
	cout << "Testing NodeStack pop()" << endl;
	nq1.pop();
	cout << nq1 << endl;

	cout << "Testing NodeStack size()" << endl;
	cout << "Size: " << nq1.size() << endl;
	cout << nq1 << endl;

	cout << "Testing NodeStack clear()" << endl;
	nq1.clear();

	cout << "Testing NodeStack empty()" << endl;
	cout << (nq1.empty() ? "> Stack is empty\n" : "> Stack is not empty\n");

	cout << "\nTesting NodeStack full()" << endl;
	cout << (nq2.full() ? "> Stack is full\n" : "> Stack is not full\n");
	}

	cout << "\n\n***Testing ArrayStack<char>***" << endl;
	ArrayStack<char> aq1, aq2(3, 'O'), aq3(aq2);
	aq1 = aq3;
	cout << "Testing ArrayStack top()" << endl;
	cout << "Before: \n" << aq1 << endl;
	aq1.top() = 'X';
	cout << "After: \n" << aq1 << endl;
	cout << "Testing ArrayStack push()" << endl;
	aq1.push('O');
	cout << aq1 << endl;
	cout << "Testing ArrayStack pop()" << endl;
	aq1.pop();
	cout << aq1 << endl;

	cout << "Testing ArrayStack size()" << endl;
	cout << "Size: " << aq1.size() << endl;
	cout << aq1 << endl;

	cout << "Testing ArrayStack clear()" << endl;
	aq1.clear();

	cout << "Testing ArrayStack empty()" << endl;
	cout << (aq1.empty() ? "> Stack is empty\n" : "> Stack is not empty\n");

	cout << "\nTesting ArrayStack full()" << endl;
	ArrayStack<int> aqf(1000, 'O');
	cout << (aqf.full() ? "> Stack is full\n" : "> Stack is not full\n");


	cout << "\n\n***Testing NodeStack<char>***" << endl;
	NodeStack<char> nq1, nq2(3, 'A'), nq3(nq2);
	nq1 = nq3;
	cout << "Testing NodeStack top()" << endl;
	cout << "Before: \n" << nq1 << endl;
	nq1.top() = 'B';
	cout << "After: \n" << nq1 << endl;
	cout << "Testing NodeStack push()" << endl;
	nq1.push('A');
	cout << nq1 << endl;
	cout << "Testing NodeStack pop()" << endl;
	nq1.pop();
	cout << nq1 << endl;

	cout << "Testing NodeStack size()" << endl;
	cout << "Size: " << nq1.size() << endl;
	cout << nq1 << endl;

	cout << "Testing NodeStack clear()" << endl;
	nq1.clear();

	cout << "Testing NodeStack empty()" << endl;
	cout << (nq1.empty() ? "> Stack is empty\n" : "> Stack is not empty\n");

	cout << "\nTesting NodeStack full()" << endl;
	cout << (nq2.full() ? "> Stack is full\n" : "> Stack is not full\n");
	return 0;
}
