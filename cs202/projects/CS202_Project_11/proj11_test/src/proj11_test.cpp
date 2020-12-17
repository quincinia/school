#include <VectorRecursion/VectorRecursion.hpp>
#include <fstream>
#include <chrono>
using namespace std;
//This code is my own work. It was written without consulting a tutor or code written by other students.

int main()
{
	fstream file;
	file.open("RandomData.txt");
	cout << (file.is_open() ? "File opened." : "File is not open.") << endl;
	vector<int> vecInt;
	int val;
	while (!file.eof()) {
		file >> val;
		vecInt.push_back(val);
	}
	size_t i = 0, j = vecInt.size()-1;
	vector_resort(vecInt);
	for (; i < j; ++i) { //assuming vector is not empty
		if (vecInt[i] > vecInt[i+1])
			break;
	}
	if (i == j) {
		cout << "Vector is sorted!" << endl;
	} else {
		cout << "Vector is NOT sorted!" << endl;
	}
	cout << "144 ";
	if (vector_research(vecInt, 144) == vecInt.end()) {
		cout << "is NOT within the vector!" << endl;
	} else {
		cout << "is located at position: " << vector_research(vecInt, 144) - vecInt.begin() << endl;
		cout << "Value: " << *vector_research(vecInt, 144) << endl;
	}

	cout << "-1 ";
	if (vector_research(vecInt, -1) == vecInt.end()) {
		cout << "is NOT within the vector!" << endl;
	} else {
		cout << "is located at position: " << vector_research(vecInt, -1) - vecInt.begin() << endl;
		cout << "Value: " << *vector_research(vecInt, -1) << endl;
	}

	cout << "600 ";
	if (vector_research(vecInt, 600) == vecInt.end()) {
		cout << "is NOT within the vector!" << endl;
	} else {
		cout << "is located at position: " << vector_research(vecInt, 600) - vecInt.begin() << endl;
		cout << "Value: " << *vector_research(vecInt, 600) << endl;
	}
	file.close();

	return 0;
}
