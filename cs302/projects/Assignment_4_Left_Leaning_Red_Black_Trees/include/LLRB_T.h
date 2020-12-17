#ifndef LLRB_T_H
#define LLRB_T_H
#include <memory>

template <class T>
class RBNode;

template <class T>
using nodePtr = std::shared_ptr<RBNode<T>>;

template <class T>
class LLRB_T
{
	private:
		nodePtr<T> root;
		static nodePtr<T> rotateLeft(nodePtr<T> axis);
		static nodePtr<T> rotateRight(nodePtr<T> axis);
		static void colorFlip(nodePtr<T> parent);
		static nodePtr<T> fixUp(nodePtr<T> parent);
		nodePtr<T> insertRec(nodePtr<T> parent, const T& value);

		static nodePtr<T> moveRedLeft(nodePtr<T> parent);
		static nodePtr<T> moveRedRight(nodePtr<T> parent);
		static nodePtr<T> findMin(nodePtr<T> parent);
		nodePtr<T> deleteMin(nodePtr<T> parent);
		nodePtr<T> deleteRec(nodePtr<T> parent, const T& value);

		static bool IsRed(nodePtr<T>);
		nodePtr<T> findNode(nodePtr<T> start, const T& value) const;
		nodePtr<T> findParent(nodePtr<T> start, const T& value) const;

		//inorder traversal
		void traverseRec(nodePtr<T> treePtr) const;
	public:
		LLRB_T();
		~LLRB_T();
		void destroyTree(nodePtr<T> subTreePtr);
		bool insert(const T& value);
		void remove(const T& target);
		bool contains(const T& value) const;
		void printNode(const T& value) const;
		void printParent(const T& value) const;
		void traverse() const;
		//clear?
};

#endif // LLRB_T_H
