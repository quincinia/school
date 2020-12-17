#ifndef NODESTACK_H //nodestack declaration
#define NODESTACK_H
#include "Node.hpp"
#include <iostream>
template <typename T> std::ostream & operator<<(std::ostream & os, const NodeStack<T> & nodeStack);

template <typename U>
class NodeStack
{
	friend std::ostream & operator<<<U>(std::ostream & os, const NodeStack<U> & nodeStack);

	public:
		NodeStack(); //(1)
		NodeStack(size_t count, const U & value); //(2)
		NodeStack(const NodeStack & other); //(3)
		~NodeStack(); //(4)
		NodeStack & operator= (const NodeStack & rhs); //(5)
		U & top(); //(6a)
		const U & top() const; //(6b)
		void push(const U & value); //(7)
		void pop(); //(8)
		size_t size() const; //(9)
		bool empty() const; //(10)
		bool full() const; //(11)
		void clear(); //(12)
		void serialize(std::ostream & os) const; //(13)

	private:
		void deepCopy(Node<U> * curr);
		Node<U> * m_top;
};

//nodestack implementations
template <typename U>
NodeStack<U>::NodeStack()
	: m_top(nullptr)
{}

template <typename U>
NodeStack<U>::NodeStack(size_t count, const U & value)
	: m_top(nullptr)
{
	Node<U> ** curr = &m_top;
	for (size_t i = 0; i < count; ++i) {
		try {
			*curr = new Node<U>(value); //not sure if this needs the <U>
		} catch (std::bad_alloc) {
			delete *curr;
			*curr = nullptr;
			std::cerr << "Allocation error!" << std::endl;
		}
		curr = &((*curr)->m_next);
	}
}

template <typename U>
void NodeStack<U>::push(const U & value)
{
	try {
		m_top = new Node<U>(value, m_top);
	} catch (std::bad_alloc) {
		std::cerr << "Allocation error!" << std::endl;
		//cant really delete m_top because then you would lose all the other pointers
		//can make a temp variable that saves the old m_top but it isn't too necessary
	}
}

template <typename U>
void NodeStack<U>::deepCopy(Node<U> * curr)
{
	if (curr->m_next != nullptr) //moves to the end of the stack
		deepCopy(curr->m_next);
	push(curr->m_data); //pushes items in reverse order
}

template <typename U>
bool NodeStack<U>::empty() const
{
	return m_top == nullptr;
}

template <typename U>
void NodeStack<U>::pop()
{
	if (empty()) {
		std::cout << "Stack empty, cannot pop" << std::endl;
		return;
	}
	Node<U> * temp = m_top->m_next;
	delete m_top;
	m_top = temp;
}

template <typename U>
void NodeStack<U>::clear()
{
	while (!empty())
		pop();
}

template <typename U>
NodeStack<U>::NodeStack(const NodeStack<U> & other)
	: m_top(nullptr)
{
	/*if (!empty()) //technically this doesn't need to be here
		clear();*/
	deepCopy(other.m_top);

}

template <typename U>
NodeStack<U>::~NodeStack()
{
	clear();
}

template <typename U>
NodeStack<U> & NodeStack<U>::operator=(const NodeStack<U> & rhs)
{
	if (this != &rhs) {
		if (!empty())
			clear();
		deepCopy(rhs.m_top);
	}
	return *this;
}

template <typename U>
U & NodeStack<U>::top()
{
	return m_top->m_data;
}

template <typename U>
const U & NodeStack<U>::top() const
{
	return m_top->m_data;
}

template <typename U>
size_t NodeStack<U>::size() const
{
	size_t size = 0;
	Node<U> * curr = m_top;
	while (curr != nullptr) {
		++size;
		curr = curr->m_next;
	}
	return size;
}

template <typename U>
bool NodeStack<U>::full() const
{
	return 0;
}

template <typename U>
void NodeStack<U>::serialize(std::ostream & os) const
{
	if (empty())
		std::cout << "List is empty." << std::endl;
	for (Node<U> * curr = m_top; curr != nullptr; curr = curr->m_next)
		os << curr->m_data << std::endl;
}

template <typename U>
std::ostream & operator<<(std::ostream & os, const NodeStack<U> & nodeStack)
{
	nodeStack.serialize(os);
	return os;
}
#endif // NODESTACK_H
