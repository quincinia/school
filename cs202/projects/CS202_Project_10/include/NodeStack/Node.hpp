#ifndef NODE_HPP_
#define NODE_HPP_
//node class declaration
#include <cstddef>
//forward declaration of NodeStack
template <typename> class NodeStack;
template <typename T>
class Node
{
	friend class NodeStack<T>;
	public:
		Node();
		Node(const T & data, Node * next = nullptr);
		T & data();
		const T & data() const;

	private:
		Node * m_next;
		T m_data;
};

//class template implementations
//template sample did not include implementation for the default constructor, so it is omitted here as well
template <typename T>
Node<T>::Node(const T & data, Node * next)
	: m_next(next),
	  m_data(data)
{}

template <typename T>
T & Node<T>::data()
{
	return m_data;
}

template <typename T>
const T & Node<T>::data() const
{
	return m_data;
}

#endif // NODE_HPP_
