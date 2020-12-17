#include <ArrayList/ArrayList.h>
#include <DataType/DataType.h>
#include <NodeList/NodeList.h>
using namespace std;

//This code is my own work. It was written without consulting a tutor or code written by other students.

int main() {
	cout << "***TESTING ARRAYLIST***" << endl;
	cout << "(1) Testing ArrayList default ctor" << endl;
	ArrayList ar1;
	cout << ar1 << endl;

	cout << "(2) Testing ArrayList parameterized ctor" << endl;
	DataType values(5, 6.01);
	ArrayList ar2(3, values);
	cout << ar2 << endl;

	cout << "(3) Testing ArrayList copy ctor" << endl;
	ArrayList ar3(ar2);
	cout << ar3 << endl;

	cout << "(4) Testing ArrayList dtor\n" << endl;
	{ ArrayList ar4(ar3); }

	cout << "(5) Testing ArrayList Assignment Operator" << endl;
	ar1 = ar3;
	cout << ar1 << endl;


	//rewrite the ArrayList insertions if u get the chance
	//commenting out most of this just to save space
	cout << "(9) Testing ArrayList insertAfter" << endl;
	//cout << "insertAfter NULL (beginning)" << endl;
	ar1.insertAfter(nullptr, DataType(1000, 0.36));
	//cout << ar1 << endl;
	//cout << "insertAfter middle" << endl;
	ar1.insertAfter(&ar1[2], DataType(1003, 0.63));
	//cout << ar1 << endl;
	//cout << "insertAfter end" << endl;
	ar1.insertAfter(&ar1[4], DataType(1005, 0.95));
	cout << ar1 << endl;

	cout << "(10) Testing ArrayList insertBefore" << endl;
	//cout << "insertBefore beginning" << endl;
	ar1.insertBefore(&ar1[0], DataType(10000, 0.366));
	//cout << ar1 << endl;
	//cout << "insertBefore middle" << endl;
	ar1.insertBefore(&ar1[3], DataType(10000, 0.633));
	//cout << ar1 << endl;
	//cout << "insertBefore NULL (end)" << endl;
	ar1.insertBefore(nullptr, DataType(10000, 0.955));
	cout << ar1 << endl;

	cout << "(6), (7), (8) Testing ArrayList front(), back(), find()" << endl;
	cout << "Front: " << *ar1.front() << endl;
	cout << "Back: " << *ar1.back() << endl;
	cout << "Found {5, 6.01} at:" << endl;
	DataType * prev;
	cout << "Pos: " << ar1.find(DataType(5, 6.01), prev) - &ar1[0] << endl;
	cout << "Pos: " << ar1.find(DataType(5, 6.01), prev, prev+1) - &ar1[0] << endl;
	cout << "Pos: " << ar1.find(DataType(5, 6.01), prev, prev+1) - &ar1[0] << endl;


	cout << "\n(11) Testing ArrayList erase" << endl;
	ar1.erase(&ar1[4]);
	cout << ar1 << endl;

	cout << "(12) Testing ArrayList operator[]" << endl;
	cout << "Pos 7:" << ar1[7] << endl;
	cout << "Pos 5:" << ar1[5] << endl;
	cout << "Pos 4:" << ar1[4] << endl;

	cout << "\n(13) Testing ArrayList size()" << endl;
	cout << "Size: " << ar1.size() << endl;

	cout << "\n(14), (15) Testing ArrayList empty() and clear()" << endl;
	ar1.clear();
	cout << ar1 << endl;
	if (ar1.empty())
		cout << "ArrayList is empty" << endl;
	else
		cout << "ArrayList is NOT empty" << endl;

	cout << "\n***TESTING NODELIST***" << endl;
	cout << "(1) Testing NodeList default ctor" << endl;
	NodeList n1;
	cout << n1 << endl;

	cout << "(2) Testing NodeList parameterized ctor" << endl;
	DataType test(2, 0.718);
	NodeList n2(3, test);
	cout << n2 << endl;

	cout << "(3) Testing NodeList copy ctor" << endl;
	NodeList n3(n2);
	cout << n3 << endl;

	cout << "(4) Testing NodeList dtor" << endl;
	{
		NodeList n4(n3);
		cout << n4 << endl;
	}

	cout << "(5) Testing NodeList operator=" << endl;
	NodeList nc(4, DataType(0, 0.618));
	cout << "Before copy:" << endl;
	cout << nc << endl;
	cout << "After copy:" << endl;
	nc = n3;
	cout << nc << endl;

	cout << "(9) Testing NodeList insertAfter" << endl;
	nc.insertAfter(nullptr, DataType(6, 0.67));
	//there is no way to access Node pointers that arent the front and back (or using find)
	nc.insertAfter(nc.front(), DataType(6, 0.67));
	nc.insertAfter(nc.back(), DataType(6, 0.67));
	cout << nc << endl;

	cout << "(10) Testing NodeList insertBefore" << endl;
	nc.insertBefore(nullptr, DataType(3, 0.1415));
	nc.insertBefore(nc.front(), DataType(3, 0.1415));
	nc.insertBefore(nc.back(), DataType(3, 0.1415));
	cout << nc << endl;

	cout << "(6) Testing NodeList front()" << endl;
	cout << nc.front()->data() << endl;

	cout << "\n(7) Testing NodeList back()" << endl;
	cout << nc.back()->data() << endl;

	cout << "\n(8) Testing NodeList find()" << endl;
	Node * Nprev;
	cout << "Found {6, 0.67} with Previous: " << endl;
	nc.find(DataType(6, 0.67), Nprev);
	cout << Nprev->data() << endl;
	nc.find(DataType(6, 0.67), Nprev, nc.find(DataType(6, 0.67), Nprev));
	cout << Nprev->data() << endl;
	nc.find(DataType(6, 0.67), Nprev, nc.find(DataType(6, 0.67), Nprev, nc.find(DataType(6, 0.67), Nprev)));
	cout << Nprev->data() << endl;

	cout << "\n(11) Testing NodeList erase" << endl;
	cout << "Erasing front, new value: " << nc.erase(nc.front())->data() << endl;
	cout << "Erasing back" << endl;
	nc.erase(nc.back());
	cout << "Erasing last {2, 0.718}, new value: " << nc.erase(Nprev)->data() << endl;
	cout << nc << endl;

	cout << "(12) Testing NodeList operator[]" << endl;
	cout << "Pos 0: " << nc[0] << endl;
	cout << "Pos 2: " << nc[2] << endl;
	cout << "Pos 5: " << nc[5] << endl;

	cout << "\n(13) Testing NodeList size()" << endl;
	cout << "Size: " << nc.size() << endl;

	cout << "\n(14), (15) Testing NodeList empty() and clear()" << endl;
	nc.clear();
	cout << nc << endl;
	if (nc.empty())
		cout << "NodeList is empty" << endl;
	else
		cout << "NodeList is NOT empty" << endl;
	return 0;
}
