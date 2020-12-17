#include <iostream>
#include <LLRB_T.h>
#include <RedBlackNode.h>
//see header file for definition of "nodePtr"

/* template <class T>
 * using nodePtr = std::shared_ptr<RBNode<T>>;
 */

template <class T>
LLRB_T<T>::LLRB_T()
	: root(nullptr)
{

}

template <class T>
LLRB_T<T>::~LLRB_T()
{

}

template <class T>
bool LLRB_T<T>::IsRed(nodePtr<T> node)
{
	if (node) //check if node exists
		return node->isRed;
	return false;
}

template <class T>
nodePtr<T> LLRB_T<T>::rotateLeft(nodePtr<T> axis)
{
	nodePtr<T> temp = axis->right;
	axis->right		= temp->left;
	temp->left		= axis;
	temp->isRed		= axis->isRed;
	axis->isRed		= true;

	return temp;
}

template <class T>
nodePtr<T> LLRB_T<T>::rotateRight(nodePtr<T> axis)
{
	nodePtr<T> temp = axis->left;
	axis->left		= temp->right;
	temp->right		= axis;
	temp->isRed		= axis->isRed;
	axis->isRed		= true;

	return temp;
}

template <class T>
void LLRB_T<T>::colorFlip(nodePtr<T> parent)
{
	parent->isRed = !parent->isRed;

	if (parent->left)
		parent->left->isRed = !parent->left->isRed;

	if (parent->right)
		parent->right->isRed = !parent->right->isRed;

}

template <class T>
nodePtr<T> LLRB_T<T>::fixUp(nodePtr<T> parent)
{
	//Fix right-leaning 3-nodes
	if (IsRed(parent->right))
		parent = rotateLeft(parent);

	//Fix unbalanded 4-nodes
	if (IsRed(parent->left) && IsRed(parent->left->left))
		parent = rotateRight(parent);

	//Split 4-nodes
	if (IsRed(parent->left) && IsRed(parent->right))
		colorFlip(parent);

	return parent;
}

template <class T>
nodePtr<T> LLRB_T<T>::insertRec(nodePtr<T> parent, const T& value)
{
	if (parent == nullptr)
	{
		parent = std::make_shared<RBNode<T>>(value);
		return parent;
	}

	//will not check if you are adding duplicates to the tree; handle that correctly

	//Recursively travel down tree
	if (value < parent->value())
		parent->left = insertRec(parent->left, value);
	else
		parent->right = insertRec(parent->right, value);

	//Fix tree as the recursion goes back up
	//Fix right-leaning 3-node
	if (IsRed(parent->right) && !IsRed(parent->left))
		parent = rotateLeft(parent);

	//Fix right-leaning 4-node
	if (IsRed(parent->left) && IsRed(parent->left->left))
		parent = rotateRight(parent);

	//Destroy 4-nodes on the way back up; 2-3 tree representation
	if (IsRed(parent->left) && IsRed(parent->right))
		colorFlip(parent);

	return parent;
}

template <class T>
nodePtr<T> LLRB_T<T>::moveRedLeft(nodePtr<T> parent)
{
	colorFlip(parent);

	if ((parent->right) && IsRed(parent->right->left))
	{
		parent->right = rotateRight(parent->right);
		parent		  = rotateLeft(parent);
		colorFlip(parent);
	}

	return parent;
}

template <class T>
nodePtr<T> LLRB_T<T>::moveRedRight(nodePtr<T> parent)
{
	colorFlip(parent);

	if ((parent->left) && IsRed(parent->left->left))
	{
		parent		  = rotateRight(parent);
		colorFlip(parent);
	}

	return parent;
}

template <class T>
nodePtr<T> LLRB_T<T>::findMin(nodePtr<T> parent)
{
	while (parent->left)
		parent = parent->left;

	return parent;
}

template <class T>
nodePtr<T> LLRB_T<T>::deleteMin(nodePtr<T> parent)
{
	//If the node has no children, delete it
	//a node must have a left child before it can have a right
	if (parent->left == nullptr)
		return nodePtr<T>(nullptr);

	//The next node must be part of a 3- or 4- node
	if (!IsRed(parent->left) && !IsRed(parent->left->left))
		parent = moveRedLeft(parent);

	//Continue going down tree
	parent->left = deleteMin(parent->left);

	//Fix mistakes as you go back up
	return fixUp(parent);
}

template <class T>
nodePtr<T> LLRB_T<T>::deleteRec(nodePtr<T> parent, const T& value)
{
	if (value < parent->value()) //go down left branch
	{
		if (parent->left)
		{
			//If the next node is not part of a 3- or 4-node, then make it one
			if (!IsRed(parent->left) && !IsRed(parent->left->left))
				parent = moveRedLeft(parent);

			//continue down the tree
			parent->left = deleteRec(parent->left, value);
		}
	}
	else //go down right branch
	{
		//If we can move a red left child, then do so
		if (IsRed(parent->left))
			parent = rotateRight(parent);

		//Delete a leaf
		//in this case, the parent cannot have a left child:
		//	      6
		//	     /
		//	    4
		//	   /
		//	  2
		//one might consider this as a counterexample, however this
		//arrangement cannot happen in an LLRB tree, because then it
		//would just get rotated:
		//	   4
		//	  / \
		//	 2   6
		//even if "6" had a right child, the "2" would be rotated to
		//the right anyway, so this check would be skipped
		if (parent->value() == value && (parent->right == nullptr))
			return nodePtr<T>(nullptr);

		if (parent->right)
		{
			//If the next node is not part of a 3- or 4-node, then make it one
			if (!IsRed(parent->right) && !IsRed(parent->right->left))
				parent = moveRedRight(parent);

			//If we delete an internal node, we have to swap it with its inorder successor
			if (parent->value() == value)
			{
				//swap values with inorder successor
				parent->Value = findMin(parent->right)->value();
				//delete inorder successor
				parent->right = deleteMin(parent->right);
			}
			else
			{
				parent->right = deleteRec(parent->right, value);
			}

		}
	}

	return fixUp(parent);
}

template <class T>
void LLRB_T<T>::destroyTree(nodePtr<T> subTreePtr)
{
	//may or may not be needed?
}

template <class T>
bool LLRB_T<T>::insert(const T& value)
{
	root = insertRec(root, value);
	root->isRed = false;
	return true;
}

template <class T>
void LLRB_T<T>::remove(const T& value)
{
	if (root)
	{
		root = deleteRec(root, value);

		//make sure the root is black, unless there is no root
		if (root) root->isRed = false;
	}
}

template <class T>
nodePtr<T> LLRB_T<T>::findNode(nodePtr<T> start, const T& value) const
{
	if (start)
	{
		if (start->value() == value) return start;
		if (value < start->value()) return findNode(start->left, value);
		return findNode(start->right, value);
	}
	return nodePtr<T>(nullptr);
}

template <class T>
bool LLRB_T<T>::contains(const T& value) const
{
	return findNode(root, value).get();
}

template <class T>
void LLRB_T<T>::printNode(const T& value) const
{
	nodePtr<T> node = findNode(root, value);
	if (node)
	{
		std::cout << "Value: " << value << '\t'
				  << "Color: " << (node->isRed ? "red":"black") << std::endl;
	}
	else
		std::cout << "Value does not exist in tree." << std::endl;
}

template <class T>
nodePtr<T> LLRB_T<T>::findParent(nodePtr<T> start, const T& value) const
{
	//if start == root, also return null
	if (start)
	{
		if (start->left)
			if (start->left->value() == value) return start;

		if (start->right)
			if (start->right->value() == value) return start;

		if (value < start->value()) return findParent(start->left, value);

		return findParent(start->right, value);
	}
	return nodePtr<T>(nullptr);
}

template <class T>
void LLRB_T<T>::printParent(const T& value) const
{
	nodePtr<T> node = findParent(root, value);
	if (root) {
		if (root->value() == value)
			std::cout << value << " is the root." << std::endl;
		if (node)
		{
			std::cout << "Parent of "   << value <<
						 " has value: " << node->value() <<
						 " and color: " << (node->isRed ? "red":"black") <<
						 std::endl;
		}
		return;
	}
	std::cout << "Value does not exist in tree." << std::endl;
}

template <class T>
void LLRB_T<T>::traverse() const
{
	traverseRec(root);
}

template <class T>
void LLRB_T<T>::traverseRec(nodePtr<T> treePtr) const
{
	if (treePtr)
	{
		traverseRec(treePtr->left);
		std::cout << treePtr->value() << ", " << (IsRed(treePtr) ? "Red":"Black") << std::endl;
		traverseRec(treePtr->right);
	}
}
