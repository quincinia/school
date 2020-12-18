#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>

using namespace std;

//prints all elements of the heap
void print(vector<int>& heap)
{
	for (int& i : heap)
		cout << i << " ";
	cout << endl;
}

//returns the mean of a heap
int heapmean(vector<int>& heap)
{
	int sum = 0;
	for (auto x : heap)
		sum += x;

	return sum/heap.size();
}

//generates random integers from 1 to 500
void randGen(vector<int>& heap, int size)
{
	int temp;
	srand(time(0));

	cout << "Adding: ";
	for (int i = 0; i < size; ++i)
	{
		temp = (rand() % 500) + 1;
		cout << temp << " ";
		heap.push_back(temp);
	}

	cout << endl;
}

void manualHeap(vector<int>& myHeap)
{
	char menu;
	int add;
	do {
		cin >> menu;
		switch (menu)
		{
			case 'a': {
				cin >> add;
				myHeap.push_back(add);
				push_heap(myHeap.begin(), myHeap.end());
				break;
			}
			case 'r': {
				pop_heap(myHeap.begin(), myHeap.end());
				myHeap.pop_back();
				break;
			}
			case 'm': {
				add = heapmean(myHeap);
				cout << "Adding mean: " << add << endl;
				myHeap.push_back(add);
				push_heap(myHeap.begin(), myHeap.end());
				break;
			}
		}
	} while (menu != 'x');
}

//change main as needed
int main()
{
	vector<int> heap;
	randGen(heap, 100);
	cout << "new heap: ";
	make_heap(heap.begin(), heap.end());
	print(heap);

	cout << "max element is: " << heap[0] << endl;

	int mean;
	cout << "mean element is: " << (mean = heapmean(heap)) << endl;
	cout << "adding mean..." << endl;
	heap.push_back(mean);
	push_heap(heap.begin(), heap.end());

	cout << "deleting the max element..." << endl;
	pop_heap(heap.begin(), heap.end());
	heap.pop_back();

	cout << "new heap: ";
	print(heap);

	/*
	make_heap(heap.begin(), heap.end());
	print(heap);

	pop_heap(heap.begin(), heap.end());
	print(heap);

	heap.pop_back();
	make_heap(heap.begin(), heap.end());
	print(heap);
	*/
	return 0;
}
