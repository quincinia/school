#include <iostream>
#include <ArrayQueue/ArrayQueue.h>
#include <NodeQueue/NodeQueue.h>
using namespace std;

//This code is my own work. It was written without consulting a tutor or code written by other students.

int main()
{

	cout << "***Testing ArrayQueue***" << endl;
	ArrayQueue aq1, aq2(3, DataType(1, 0.732)), aq3(aq2);
	aq1 = aq3;
	cout << "Testing ArrayQueue front()" << endl;
	cout << "Before: \n" << aq1 << endl;
	aq1.front() = DataType(2, 0.236);
	cout << "After: \n" << aq1 << endl;
	cout << "Testing ArrayQueue back()" << endl;
	aq1.back() = DataType(2, 0.4494);
	cout << "After: \n" << aq1 << endl;
	cout << "Testing ArrayQueue push()" << endl;
	aq1.push(DataType(2, 0.64575));
	cout << aq1 << endl;
	cout << "Testing ArrayQueue pop()" << endl;
	aq1.pop();
	cout << aq1 << endl;

	cout << "Testing ArrayQueue size()" << endl;
	cout << "Size: " << aq1.size() << endl;
	cout << aq1 << endl;

	cout << "Testing ArrayQueue clear()" << endl;
	aq1.clear();

	cout << "Testing ArrayQueue empty()" << endl;
	cout << (aq1.empty() ? "> Queue is empty\n" : "> Queue is not empty\n");

	cout << "\nTesting ArrayQueue full()" << endl;
	ArrayQueue aqf(1000, DataType(5, 0.555));
	cout << (aqf.full() ? "> Queue is full\n" : "> Queue is not full\n");


	cout << "\n\n***Testing NodeQueue***" << endl;
	NodeQueue nq1, nq2(3, DataType(1, 0.732)), nq3(nq2);
	nq1 = nq3;
	cout << "Testing NodeQueue front()" << endl;
	cout << "Before: \n" << nq1 << endl;
	nq1.front() = DataType(2, 0.236);
	cout << "After: \n" << nq1 << endl;
	cout << "Testing NodeQueue back()" << endl;
	nq1.back() = DataType(2, 0.4494);
	cout << "After: \n" << nq1 << endl;
	cout << "Testing NodeQueue push()" << endl;
	nq1.push(DataType(2, 0.64575));
	cout << nq1 << endl;
	cout << "Testing NodeQueue pop()" << endl;
	nq1.pop();
	cout << nq1 << endl;

	cout << "Testing NodeQueue size()" << endl;
	cout << "Size: " << nq1.size() << endl;
	cout << nq1 << endl;

	cout << "Testing NodeQueue clear()" << endl;
	nq1.clear();

	cout << "Testing NodeQueue empty()" << endl;
	cout << (nq1.empty() ? "> Queue is empty\n" : "> Queue is not empty\n");

	cout << "\nTesting NodeQueue full()" << endl;
	cout << (nq2.full() ? "> Queue is full\n" : "> Queue is not full\n");
}
