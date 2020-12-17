#ifndef ARRAYSTACK_HPP_
#define ARRAYSTACK_HPP_
#include <iostream>
//arraystack declaration
const size_t ARRAY_CAPACITY = 1000;
template <typename> class ArrayStack;
template <typename T> std::ostream & operator<<(std::ostream & os, const ArrayStack<T> & arrayStack);
template <typename T>
class ArrayStack {
	friend std::ostream & operator<<<T>(std::ostream & os, //(i)
	const ArrayStack<T> & arrayStack);
	public:
		ArrayStack(); //(1)
		ArrayStack(size_t count, const T & value); //(2)
		ArrayStack(const ArrayStack & other); //(3)
		~ArrayStack(); //(4)
		ArrayStack<T> & operator= (const ArrayStack<T> & rhs); //(5)
		T & top(); //(6a)
		const T & top() const; //(6b)
		void push(const T & value); //(7)
		void pop(); //(8)
		size_t size() const; //(9)
		bool empty() const; //(10)
		bool full() const; //(11)
		void clear(); //(12)
		void serialize(std::ostream & os) const; //(13)
	private:
		T m_array[ARRAY_CAPACITY];
		size_t m_top; //m_top will reflect the size of the stack; eg. if there are 2 items, m_top will equal 2
};

//arraystack implementations
template <typename T>
ArrayStack<T>::ArrayStack()
	: m_top(0)
{}

template <typename T>
ArrayStack<T>::ArrayStack(size_t count, const T & value)
	: m_top(count)
{
	for (size_t i = 0; i < count; ++i)
		m_array[i] = value;
}

template <typename T>
ArrayStack<T>::ArrayStack(const ArrayStack & other)
	: m_top(other.m_top)
{
	for (size_t i = 0; i < other.m_top; ++i)
		m_array[i] = other.m_array[i];
}

template <typename T>
ArrayStack<T>::~ArrayStack()
{}

template <typename T>
ArrayStack<T> & ArrayStack<T>::operator=(const ArrayStack<T> & rhs)
{
	if (this != &rhs) {
		for (size_t i = 0; i < ARRAY_CAPACITY; ++i)
			m_array[i] = rhs.m_array[i];
		m_top = rhs.m_top;
	}
	return *this;
}

template <typename T>
T & ArrayStack<T>::top()
{
	return m_array[m_top-1];
}

template <typename T>
const T & ArrayStack<T>::top() const
{
	return m_array[m_top-1];
}

template <typename T>
void ArrayStack<T>::push(const T & value)
{
	if (m_top != ARRAY_CAPACITY) {
		m_array[m_top] = value;
		++m_top;
	} else {
		std::cout << "Stack full, cannot push" << std::endl;
	}
}

template <typename T>
void ArrayStack<T>::pop()
{
	if (m_top)
		--m_top;
}

template <typename T>
size_t ArrayStack<T>::size() const
{
	return m_top;
}

template <typename T>
bool ArrayStack<T>::empty() const
{
	return m_top ? 0 : 1;
}

template <typename T>
bool ArrayStack<T>::full() const
{
	return (m_top == ARRAY_CAPACITY);
}

template <typename T>
void ArrayStack<T>::clear()
{
	m_top = 0;
}

template <typename T>
std::ostream & operator<<(std::ostream & os, const ArrayStack<T> & arrayStack)
{
	arrayStack.serialize(os);
	return os;
}

template <typename T>
void ArrayStack<T>::serialize(std::ostream & os) const
{
	if (m_top == 0)
		os << "ArrayStack is empty." << std::endl;
	for (int i = m_top-1; i >= 0; --i)
		os << m_array[i] << std::endl;
}
#endif // ARRAYSTACK_HPP_
