#include <VectorRecursion/VectorRecursion.hpp>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

void fill(vector<int> & fill, int size)
{
    fill.clear();
    int gen;
    for (int i = 0; i < size; ++i) {
        gen = rand() % (5*size + 1);
        fill.push_back(gen);
    }
}

chrono::duration<double, milli> sort_test(vector<int> & test, int size)
{
    fill(test, size);
        auto t1 = chrono::steady_clock::now();
    vector_resort(test);
        auto t2 = chrono::steady_clock::now();
        chrono::duration<double, milli> debug = t2-t1;
        return debug;
}

chrono::duration<double, milli> STDsort_test(vector<int> & test, int size)
{
    fill(test, size);
        auto t1 = chrono::steady_clock::now();
    std::sort(test.begin(), test.end());
        auto t2 = chrono::steady_clock::now();
        chrono::duration<double, milli> debug = t2-t1;
        return debug;
}


chrono::duration<double, milli> search_test(vector<int> & test, int size) {
        fill(test, size);
        std::sort(test.begin(), test.end());
    int search = rand() % size;
        auto t1 = chrono::steady_clock::now();
        vector_research(test, test[search]);
        auto t2 = chrono::steady_clock::now();
        chrono::duration<double, milli> debug = t2-t1;
        return debug;
}

chrono::duration<double, milli> STDsearch_test(vector<int> & test, int size) {
        fill(test, size);
        std::sort(test.begin(), test.end());
        int search = rand() % size;
        auto t1 = chrono::steady_clock::now();
        std::binary_search(test.begin(), test.end(), test[search]);
        auto t2 = chrono::steady_clock::now();
        chrono::duration<double, milli> debug = t2-t1;
        return debug;
}

//This code is my own work. It was written without consulting a tutor or code written by other students.

int main() {
    srand(time(0)); //put this in main

    vector<int> vec, STL;
        cout << "\n***Testing sorts***" << endl;
//100 elements
    cout << "For sorting 100 elements:" << endl;
        chrono::duration<double, milli> resort(0), STDsort(0); //don't know if this is the same as zero()
    for (int i = 0; i < 100; ++i) {
                resort += sort_test(vec, 10000);
                STDsort += STDsort_test(STL, 10000);
    }
        cout << "vector_resort: " << resort.count()/100 << endl;
        cout << "std::sort: " << STDsort.count()/100 << endl;

//10,000 elements
    cout << "\nFor sorting 10,000 elements:" << endl;
        resort = STDsort = chrono::duration<double, milli>::zero();
    for (int i = 0; i < 100; ++i) {
        resort += sort_test(vec, 10000);
        STDsort += STDsort_test(STL, 10000);
    }
    cout << "vector_resort: " << resort.count()/100 << endl;
    cout << "std::sort: " << STDsort.count()/100 << endl;

//1,000,000 elements
    cout << "\nFor sorting 1,000,000 elements:" << endl;
        resort = STDsort = chrono::duration<double, milli>::zero();
        for (int i = 0; i < 10; ++i) { //testing 1m 100x is too much
        resort += sort_test(vec, 1000000); //might need to do the divisions in here
        STDsort += STDsort_test(STL, 1000000);
    }
        cout << "vector_resort: " << resort.count()/10 << endl;
        cout << "std::sort: " << STDsort.count()/10 << endl;





//searching

        cout << fixed;
        cout << "\n***Testing searches***" << endl;
        cout << "For searching through 100 elements:" << endl;
        chrono::duration<double, milli> research(0), bsearch(0);
        for (int i = 0; i < 100; ++i) {
                research += search_test(vec, 100);
                bsearch += STDsearch_test(vec, 100);
        }
        cout << "vector_research: " << research.count()/100 << endl;
        cout << "std::binary_search: " << bsearch.count()/100 << endl;




        cout << "\nFor searching through 10,000 elements:" << endl;
        research = bsearch = chrono::duration<double, milli>::zero();
        for (int i = 0; i < 100; ++i) {
                research += search_test(vec, 10000);
                bsearch += STDsearch_test(vec, 10000);
        }
        cout << "vector_research: " << research.count()/100 << endl;
        cout << "std::binary_search: " << bsearch.count()/100 << endl;





        cout << "\nFor searching through 1,000,000 elements:" << endl;
        research = bsearch = chrono::duration<double, milli>::zero();
        for (int i = 0; i < 10; ++i) {
                research += search_test(vec, 1000000);
                bsearch += STDsearch_test(vec, 1000000);
        }
        cout << "vector_research: " << research.count()/10 << endl;
        cout << "std::binary_search: " << bsearch.count()/10 << endl;
    return 0;
}

