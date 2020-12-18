#ifndef REDBLACKNODE_H
#define REDBLACKNODE_H
#include <memory>

template <class>
class LLRB_T;

template <class T>
class RBNode
{
	friend class LLRB_T<T>; //just to make things easier to read
	private:
		T Value;
		bool isRed;
		std::shared_ptr<RBNode> left;
		std::shared_ptr<RBNode> right;

	public:
		RBNode();
		RBNode(const T& value, bool color = 1);
		T value() const;
		void setValue(const T& item);
		std::shared_ptr<RBNode> getLeft() const;
		void setLeft(std::shared_ptr<RBNode>);
		std::shared_ptr<RBNode> getRight() const;
		void setRight(std::shared_ptr<RBNode>);

		//isLeaf?
};

#endif // REDBLACKNODE_H
