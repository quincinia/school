#include <iostream>
#include <fstream> //may not be needed anymore
#include <ctime>
#include <cstdlib>
#include <random>
#include <bubblesort.hpp> //<chrono> is already included in these
#include <quicksort.hpp>

using namespace std;

void genRand(int[], int[], int size); //fills 2 arrays of the same size with random numbers from [0, 1000000]
void printArray(int[], int size); //for debugging purposes

int main()
{
	srand(time(0));
	BubbleSort Bubblesorter;
	//the 100k sets start to overflow, so using long double and long int to try and get around it
	//[0] = stats, [1] = Resort stats
	long double bubbleSortStats[2] = {0, 0};
	//[0] = comps, [1] = swaps
	unsigned long long int bubbleSortCompsSwaps[2][2] = {{0, 0}, {0, 0}};
	QuickSort Quicksorter;
	long double quickSortStats[2] = {0, 0};
	unsigned long long int quickSortCompsSwaps[2][2] = {{0, 0}, {0, 0}};

/* 1. generate numbers of size category (1k, 10k, 100k)
 * 2. sort both arrays, add time/comps/swaps to total
 * 3. resort sorted arrays, add time/comps/swaps to total
 * 4. repeat steps (1)-(3) 10 times
 * 5. take average time/comps/swaps of sorts
 * 6. take average time/comps/swaps of resorts
 * 7. print out data
 * 8. repeat (1)-(7) for all size categories
 */

	for (int i = 1000; i != 1000000; i *= 10) {
		for (int j = 0; j < 10; ++j) {
			int* a = new int[i];
			int* b = new int[i];
			genRand(a, b, i);
			//sort elements the first time
			Bubblesorter.sort(&a[0], &a[i]);
			bubbleSortStats[0] += Bubblesorter.time();
			bubbleSortCompsSwaps[0][0] += Bubblesorter.compares();
			bubbleSortCompsSwaps[0][1] += Bubblesorter.swaps();

			Quicksorter.sort(&b[0], &b[i]);
			quickSortStats[0] += Quicksorter.time();
			quickSortCompsSwaps[0][0] += Quicksorter.compares();
			quickSortCompsSwaps[0][1] += Quicksorter.swaps();
			Quicksorter.reset();

			//sort elements the second time
			Bubblesorter.sort(&a[0], &a[i]);
			bubbleSortStats[1] += Bubblesorter.time();
			bubbleSortCompsSwaps[1][0] += Bubblesorter.compares();
			bubbleSortCompsSwaps[1][1] += Bubblesorter.swaps();

			Quicksorter.sort(&b[0], &b[i]);
			quickSortStats[1] += Quicksorter.time();
			quickSortCompsSwaps[1][0] += Quicksorter.compares();
			quickSortCompsSwaps[1][1] += Quicksorter.swaps();
			Quicksorter.reset();

			delete [] a;
			delete [] b;
		}
		cout << "For " << i << " items: " << endl;
		cout << "=== BUBBLESORT ===" << endl;
		cout << "Average time: " << bubbleSortStats[0]/10 << endl; //not sure if averages should be computed inline or here
		cout << "Average comparisons: " << bubbleSortCompsSwaps[0][0]/10 << endl;
		cout << "Average swaps: " << bubbleSortCompsSwaps[0][1]/10 << endl;
		cout << "--- Resorting averages ---" << endl;
		cout << "Time: " << bubbleSortStats[1]/10 << endl;
		cout << "Comparisons: " << bubbleSortCompsSwaps[1][0]/10 << endl;
		cout << "Swaps: " << bubbleSortCompsSwaps[1][1]/10 << endl; //should always be 0
		cout << endl;
		cout << "=== QUICKSORT ===" << endl;
		cout << "Average time: " << quickSortStats[0]/10 << endl;
		cout << "Average comparisons: " << quickSortCompsSwaps[0][0]/10 << endl;
		cout << "Average swaps: " << quickSortCompsSwaps[0][1]/10 << endl;
		cout << "--- Resorting averages ---" << endl;
		cout << "Time: " << quickSortStats[1]/10 << endl;
		cout << "Comparisons: " << quickSortCompsSwaps[1][0]/10 << endl;
		cout << "Swaps: " << quickSortCompsSwaps[1][1]/10 << endl; //note on quickResort swaps: because of how my implementation works, there is guaranteed to be some swaps (when "begin" and "pivot" are equal or on top of each other)
		cout << endl;

		//reset everything for next loop
		bubbleSortStats[0] = 0.f;
		bubbleSortStats[1] = 0.f;
		bubbleSortCompsSwaps[0][0] = 0;
		bubbleSortCompsSwaps[0][1] = 0;
		bubbleSortCompsSwaps[1][0] = 0;
		bubbleSortCompsSwaps[1][1] = 0;

		quickSortStats[0] = 0.f;
		quickSortStats[1] = 0.f;
		quickSortCompsSwaps[0][0] = 0;
		quickSortCompsSwaps[0][1] = 0;
		quickSortCompsSwaps[1][0] = 0;
		quickSortCompsSwaps[1][1] = 0;
	}

	return 0;
}

void genRand(int a[], int b[], int size) {
	default_random_engine gen(chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> rNum(0, 1000000);
	for (int i = 0; i < size; ++i)
		a[i] = b[i] = rNum(gen);
}

void printArray(int arr[], int size) {
	for (int i = 0; i < size; ++i)
		cout << arr[i] << endl;
}
