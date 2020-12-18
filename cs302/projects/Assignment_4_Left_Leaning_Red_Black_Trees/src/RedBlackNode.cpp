#include <RedBlackNode.h>

template <class T>
RBNode<T>::RBNode()
	: isRed(true),
	  left(nullptr),
	  right(nullptr)
{

}

template <class T>
RBNode<T>::RBNode(const T& item, bool color)
	: Value(item),
	  isRed(color),
	  left(nullptr),
	  right(nullptr)
{

}

template <class T>
T RBNode<T>::value() const
{
	return Value;
}

template <class T>
void RBNode<T>::setValue(const T& item)
{
	Value = item;
}



template <class T>
std::shared_ptr<RBNode<T>> RBNode<T>::getLeft() const
{
	return left;
}

template <class T>
void RBNode<T>::setLeft(std::shared_ptr<RBNode<T>> newL)
{
	left = newL;
}

template <class T>
std::shared_ptr<RBNode<T>> RBNode<T>::getRight() const
{
	return right;
}

template <class T>
void RBNode<T>::setRight(std::shared_ptr<RBNode<T>> newR)
{
	right = newR;
}
