#ifndef VECTORRECURSION_HPP
#define VECTORRECURSION_HPP
#include <vector>
#include <iostream>
//quicksort algo:
//1. choose pivot (usually set to vec.begin())
//1a. (auto) pivot = vec.begin()
//1b. can also use size_t to work with indices instead of iterators

//2. everything <= pivot goes before it (use swap)
//2a. loop thru all indices and check

//3. take indices found in (2) and send them to partitioning function
//3a. partition should only sort [a, b)
//3b. send in (vec.begin(), pivot) and (pivot+1, end)

//(partitioning function)
//4a. set/sort pivot
//4b. sort left
//4c. sort right
//4d. no sort when range only has 1 element
template <typename T>
void swap(T & a, T & b)
{
    T temp = a;
    a = b;
    b = temp;
}


template <typename T>
void sort(/*typename std::vector<T>::iterator*/ T begin, /*typename std::vector<T>::iterator*/ T end) //this should not use "std::vector<T>::iterator" because begin and end are already of that type
{
    if (end - begin <= 1) return; //range is sorted if it has 1 or 0 elements
    auto beginCpy = begin;
    auto pivot = begin++;
    for (; begin != end; ++begin) {
        if (*begin <= *pivot) {
            swap(*pivot, *begin);
            ++pivot;
            swap(*pivot, *begin);
        }
    }
	::sort(beginCpy, pivot);
	::sort(pivot+1, end); //pivot+1 is very important
}

template <typename T>
void vector_resort(std::vector<T> & vec)
{
    if (vec.empty()) {
        std::cout << "Empty vector, cannot be sorted" << std::endl;
        return;
    }
	::sort(vec.begin(), vec.end());
}

//vector_research function
template <typename T>
int binary_search(std::vector<T> & vec, const T & value, size_t beg, size_t end)
{
    size_t pivot = (beg + end)/2;
    if (beg == end) {
        if (pivot == value)
            return pivot;
        return -1;
    }
	if (value > (int)vec[pivot]) {
        beg = pivot + 1;
		return binary_search<T>(vec, value, beg, end);
	} else if (value < (int)vec[pivot]) {
		if (pivot != 0) {
			end = pivot - 1;
		} else {
			end = pivot;
		}
		return binary_search<T>(vec, value, beg, end);
    }
    return pivot;
}

template <typename T>
typename std::vector<T>::iterator vector_research(std::vector<T> & vec, const T & value)
{
    //include check for empty vector?
	int search = binary_search<T>(vec, value, 0, vec.size()-1);
    if (search == -1)
        return vec.end();
    return (vec.begin() + search);
}
#endif // VECTORRECURSION_HPP
