#ifndef BUBBLESORT_H
#define BUBBLESORT_H
#include <utility> //swap
#include <chrono>

class BubbleSort {
	public:
		BubbleSort() : Compares(0), Swaps(0), CPUTime(std::chrono::duration<double>::zero()) {};
		template <typename T>
		void sort(T begin, T end);

		unsigned long long int compares() {return Compares;}
		unsigned long long int swaps() {return Swaps;}
		double time() {return CPUTime.count();}
	private:
		unsigned long long int Compares;
		unsigned long long int Swaps;
		std::chrono::duration<double> CPUTime;
};

template <typename T>
void BubbleSort::sort(T begin, T end)
{
	Compares = 0; //reset values before sorting
	Swaps = 0;
	CPUTime = std::chrono::duration<double>::zero();
	auto t1 = std::chrono::steady_clock::now();
	if (end - begin <= 1) { //range is sorted if it has 1 or 0 elements
		auto t2 = std::chrono::steady_clock::now();
		CPUTime += (t2 - t1);
		return;
	}

	bool sorted;
	do {
		sorted = true;
		for (auto i = begin + 1; i != end; ++i) {
			if (*(i-1) < *i) {
				++Compares;
				std::swap(*i, *(i-1));
				++Swaps;
				sorted = false;
			} else {
				++Compares;
			}
		}
	} while (!sorted);
	auto t2 = std::chrono::steady_clock::now();
	CPUTime += (t2 - t1);
}

#endif // BUBBLESORT_H
