//arrayqueue implementations

#include <ArrayQueue/ArrayQueue.h>
using namespace std;

ArrayQueue::ArrayQueue()
	: m_front(0),
	  m_back(0),
	  m_size(0)
{
	cout << "ArrayQueue Default Constructor" << endl;
}

ArrayQueue::ArrayQueue(size_t count, const DataType & value)
	: m_front(0),
	  m_back(count-1),
	  m_size(count)
{
	cout << "ArrayQueue Parameterized Constructor" << endl;
	for (size_t i = 0; i < count; ++i)
		m_array[i] = value;
}

ArrayQueue::ArrayQueue(const ArrayQueue & other)
	: m_front(0),
	  m_back(other.m_back),
	  m_size(other.m_size)
{
	cout << "ArrayQueue Copy Constructor" << endl;
	for (size_t i = 0; i < m_size; ++i)
		m_array[i] = other.m_array[i];
}

ArrayQueue::~ArrayQueue()
{
	cout << "ArrayQueue Destructor" << endl;
}

//"Note: Consider whether you actually need to implement this."
//not sure if this actually needs to be implemented???
ArrayQueue & ArrayQueue::operator=(const ArrayQueue & rhs)
{
	cout << "ArrayQueue operator=" << endl;
	if (this != &rhs) {
		for (size_t i = 0; i < ARRAY_CAPACITY; ++i)
			m_array[i] = rhs.m_array[i];
		m_front = rhs.m_front;
		m_back = rhs.m_back;
		m_size = rhs.m_size;
	}
	return *this;
}


//always use an if statement before using front()
DataType & ArrayQueue::front()
{
	cout << "ArrayQueue front()" << endl;
	return m_array[m_front];
}

const DataType & ArrayQueue::front() const
{
	cout << "ArrayQueue front()" << endl;
	return m_array[m_front];
}


//put an if statement before using back() as well
DataType & ArrayQueue::back()
{
	cout << "ArrayQueue back()" << endl;
	return m_array[m_back];
}

const DataType & ArrayQueue::back() const
{
	cout << "ArrayQueue back()" << endl;
	return m_array[m_back];
}

void ArrayQueue::push(const DataType &value)
{
	cout << "ArrayQueue push()" << endl;
	if (m_size == ARRAY_CAPACITY) {
		cout << "Full queue, cannot push" << endl;
		return;
	}
	m_back = (m_back + 1) % ARRAY_CAPACITY;
	m_array[m_back] = value;
	++m_size;
}

void ArrayQueue::pop()
{
	cout << "ArrayQueue pop()" << endl;
	if (m_size == 0) {
		cout << "Empty queue, cannot pop" << endl;
	}
	m_front = (m_front + 1) % ARRAY_CAPACITY;
	--m_size;
}

size_t ArrayQueue::size() const
{
	cout << "ArrayQueue size()" << endl;
	return m_size;
}

bool ArrayQueue::empty() const
{
	cout << "ArrayQueue empty()" << endl;
	return m_size ? 1 : 0;
}

bool ArrayQueue::full() const
{
	cout << "ArrayQueue full()" << endl;
	return (m_size == ARRAY_CAPACITY) ? 1 : 0;
}

void ArrayQueue::clear()
{
	cout << "ArrayQueue clear()" << endl;
	m_front = 0;
	m_back = 0;
	m_size = 0;
}

void ArrayQueue::serialize(std::ostream &os) const
{
	size_t i = m_front;
	for (size_t j = 0; j < m_size; ++j) {
		os << m_array[i] << endl;
		i = (i + 1) % ARRAY_CAPACITY;
	}
}

ostream & operator<<(ostream & os, const ArrayQueue & arrayQueue)
{
	arrayQueue.serialize(os);
	return os;
}
