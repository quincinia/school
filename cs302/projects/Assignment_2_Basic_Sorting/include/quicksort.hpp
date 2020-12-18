#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <utility> //swap
#include <chrono>

class QuickSort {
	public:
		QuickSort() : Compares(0), Swaps(0), CPUTime(std::chrono::duration<double>::zero()) {};
		template <typename T>
		void sort(T begin, T end);
		void reset() {Compares = 0; Swaps = 0; CPUTime = std::chrono::duration<double>::zero();} //because quicksort is recursive, we cannot reset the values inside the function (unlike with bubblesort), so we have to do it manually

		unsigned long long int compares() {return Compares;}
		unsigned long long int swaps() {return Swaps;}
		double time() {return CPUTime.count();}
	private:
		unsigned long long int Compares;
		unsigned long long int Swaps;
		std::chrono::duration<double> CPUTime;
};

/**
 *	"begin" and "end" are iterators to the same [vector] or pointers to the same array
 */
template <typename T>
void QuickSort::sort(T begin, T end)
{
	auto t1 = std::chrono::steady_clock::now();
	if (end - begin <= 1) { //range is sorted if it has 1 or 0 elements
		auto t2 = std::chrono::steady_clock::now();
		CPUTime += (t2 - t1);
		return;
	}

	auto beginCpy = begin;
	auto pivot = begin++;
	for (; begin != end; ++begin) {
		if (*begin <= *pivot) {
				++Compares;
			std::swap(*pivot, *begin);
				++Swaps;
			++pivot;
			std::swap(*pivot, *begin);
				++Swaps;
		} else {
				++Compares; //comparison still happened even if nothing changed
		}
	}
	auto t2 = std::chrono::steady_clock::now();
	CPUTime += (t2 - t1);

	sort(beginCpy, pivot);
	sort(pivot+1, end); //pivot+1 is very important
}

#endif // QUICKSORT_H
