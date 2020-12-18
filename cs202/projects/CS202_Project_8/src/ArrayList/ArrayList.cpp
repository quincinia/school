//implementation of ArrayList functions
#include <ArrayList/ArrayList.h>
#include <iostream>

//note: not sure if <new> is needed in order for bad_alloc to work
using namespace std;


//note: constructors are incomplete until resize operations are finished

ostream & operator<< (ostream & os, const ArrayList & arraylist)
{
	cout << "Size = " << arraylist.m_size << endl;
	cout << "Capacity = " << arraylist.m_maxsize << endl;
	cout << "Elements:\n";
	for (size_t i = 0; i < arraylist.m_size; ++i) {
		os << "[" << i << "]: " << arraylist.m_array[i] << endl;
	}
	return os;
}

ArrayList::ArrayList(size_t count, const DataType & value)
	: m_size(count),
	  m_maxsize(count) //parameterized ctor only allocates as much as it needs to, then resizes if needed
{
	try {
		m_array = new DataType[20];
	} catch (bad_alloc & ex) {
		delete [] m_array;
		cerr << "Allocation error!\n";
	}

	for (size_t i = 0; i < count; ++i) {
		m_array[i] = value;
	}
}

ArrayList::ArrayList()
	: ArrayList(0, DataType()) //new [](0) has weird implications so make sure the array is never dereferenced
{ }

ArrayList::ArrayList(const ArrayList & other)
	: m_size(other.m_size),
	  m_maxsize(other.m_size)
{
	try {
		m_array = new DataType[m_maxsize];
	} catch (bad_alloc & ex) {
		delete [] m_array;
		cerr << "Allocation error!\n";
	}
	for (size_t i = 0; i < m_size; ++i) {
		m_array[i] = other.m_array[i];
	}
}

ArrayList::~ArrayList()
{
	delete [] m_array;
}

ArrayList & ArrayList::operator=(const ArrayList & rhs)
{
	if (this != &rhs) {
		delete [] m_array;
		try {
			m_array = new DataType[rhs.m_size];
		} catch (bad_alloc & ex) {
			delete [] m_array;
			cerr << "Allocation error!\n";
		}
		for (size_t i = 0; i < rhs.size(); ++i) {
			m_array[i] = rhs[i];
		}
		m_size = rhs.size();
		m_maxsize = rhs.size();
	}
	return *this;
}

DataType * ArrayList::front()
{
	if (m_size == 0 || m_maxsize == 0 || m_array == nullptr) {
		return nullptr;
	} else {
		return m_array;
	}
}

DataType * ArrayList::back()
{
	if (m_size == 0 || m_maxsize == 0 || m_array == nullptr) {
		return nullptr;
	} else {
		return &m_array[m_size-1];
	}
}


//find algo (dont look at this)
/* 1. if array is invalid/empty, return null, set previous to null and return null
 * 2. if start is invalid, return nulls
 * 3. set begin pointer
 * 4. loop from begin until size, looking for target as u go
 * 4a. if target is found, check pointer if its at the beginning of the array
 * 4a. if it is, previous is null, if it isnt, set previous
 */
DataType * ArrayList::find(const DataType & target, DataType *&previous, const DataType * start) //reference to a DataType pointer
{
	//normally, the start is assumed to be within the array
	if (start >= m_array && start < &m_array[m_size]) {
		//if start is inside the array, continue
	} else if (start == nullptr) {
		//if start is null, continue
	} else {
		return nullptr;
	}
	if (m_size == 0 || m_maxsize == 0 || m_array == nullptr) {
		return nullptr;
	}
	/*const DataType * begin = (start == nullptr) ? m_array : (start+1);
	for (int i = 0; (begin += i) < &m_array[m_size]; ++i) {
		if (m_array[i] == target) {
			if (begin == m_array) {
				previous = nullptr;
			} else {
				previous = &m_array[i-1];
			}
			return &m_array[i];
		}
	}*/

	int go = (start == nullptr) ? 0 : start - m_array + 1;
	for (; go < int(m_size); ++go) {
		if (m_array[go] == target) {
			if (go == 0)
				previous = nullptr;
			else
				previous = &m_array[go-1];
			return &m_array[go];
		}
	}
	previous = nullptr;
	return nullptr;
}

void ArrayList::resize(size_t count)
{
	DataType * temp;
	try {
		temp = new DataType[count];
	} catch (bad_alloc & ex) {
		delete [] temp;
		cerr << "Resize error!\n";
		throw bad_alloc();
	}
	size_t range = (count <= m_size) ? count : m_size;
	for (size_t i = 0; i < range; ++i) {
		temp[i] = m_array[i];
	}
	delete[] m_array;
	m_array = temp;
	m_size = range;
	m_maxsize = count;

}

void swap(DataType & A, DataType & B)
{
	DataType temp = A;
	A = B;
	B = temp;
}

DataType * ArrayList::insertAfter(DataType * target, const DataType & value)
{
	int pos = target - m_array + 1;
	//target is assumed to be within the array or null
	if (target == nullptr) {
		target = m_array; //assuming target should be the beginning if it is set to null
		pos = 0;
	}
	if (m_size == m_maxsize) {
		try {
			if (m_maxsize) //resizes will double capacity
				resize(m_maxsize * 2);
			else
				resize(m_maxsize+1);
		} catch (bad_alloc & ex) {
			cerr << "Resize error, returning null\n"; //assuming this is what he means by failed insertion
			return nullptr;
		}

	}
	int curr = int(m_size); //curr refers to the newly created empty space made with resize
	while (curr != pos) { //loops until curr is in the correct position (after the point labeled by target)
		swap(m_array[curr], m_array[curr-1]);
		--curr;
	}
	m_array[curr] = value;
	++m_size;
	return &m_array[curr];
	//we have to make a "pos" variable because once the array is resized we can no longer use pointer comparisons
}

DataType * ArrayList::insertBefore(DataType *target, const DataType &value)
{
	int pos = target - m_array + 1;
	(target == m_array) ? --pos : 0;
	if (target == nullptr) {
		pos = int(m_size); //if target is null, places at the end
	}
	if (m_size == m_maxsize) {
		try {
			if (m_maxsize)
				resize(m_maxsize * 2);
			else
				resize(m_maxsize+1);
		} catch (bad_alloc & ex) {
			cerr << "Resize error, returning null\n";
			return nullptr;
		}
	}
	int curr = int(m_size);
	while (curr != pos) {
		swap(m_array[curr], m_array[curr-1]);
		--curr;
	}
	m_array[curr] = value;
	++m_size;
	return &m_array[curr];
}

DataType * ArrayList::erase(DataType * target) //erase does not change capacity
{
	if (target == nullptr)
		target = m_array;
	size_t i;
	for (i = 0; i < m_size; ++i) {
		if (m_array + i == target) {
			break;
		}
	}
	m_array[i] = DataType();
	--m_size;
	for (size_t j = i; j < m_size; ++j) {
		swap(m_array[j], m_array[j+1]);
	}

	if (i == m_maxsize) {
		return nullptr;
	} else {
		return m_array + i;
	}

}

DataType & ArrayList::operator[](size_t position)
{
	return m_array[position];
}

const DataType & ArrayList::operator[](size_t position) const
{
	return m_array[position];
}

size_t ArrayList::size() const
{
	return m_size;
}

bool ArrayList::empty() const
{
	if (m_size == 0)
		return 1;
	return 0;
}

void ArrayList::clear() //clear does not change capacity
{
	for (size_t i = 0; i < m_size; ++i) {
		m_array[i] = DataType();
	}
	m_size = 0;
}
