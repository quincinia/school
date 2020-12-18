#include <BinaryNodeTree.h>
// CONSTRUCTOR AND DESTRUCTOR SECTION
template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree()
    : rootPtr(nullptr)
{
	//rootPtr should already be null
}

template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem)
    : rootPtr(std::make_shared<BinaryNode<ItemType>>(rootItem, nullptr, nullptr))
{

}

template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem, const std::shared_ptr<BinaryNodeTree<ItemType>> leftTreePtr, const std::shared_ptr<BinaryNodeTree<ItemType>> rightTreePtr)
	: rootPtr(std::make_shared<BinaryNode<ItemType>>(rootItem),
			  copyTree(leftTreePtr->rootPtr),
			  copyTree(rightTreePtr->rootPtr))
{

}

template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const std::shared_ptr<BinaryNodeTree<ItemType>>& tree)
{
	rootPtr = copyTree(tree->rootPtr);
}

template <class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::copyTree(const std::shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr) const
{
	std::shared_ptr<BinaryNode<ItemType>> temp;
	if (oldTreeRootPtr)
	{
		//create the node
		temp = std::make_shared<BinaryNode<ItemType>>(oldTreeRootPtr->getItem(), nullptr, nullptr);

		//attach the node's children
                temp->setLeftChildPtr(copyTree(oldTreeRootPtr->getLeftChildPtr()));
                temp->setRightChildPtr(copyTree(oldTreeRootPtr->getRightChildPtr()));
	}
	return temp; //temp is null by default
}

template <class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree()
{
	destroyTree(rootPtr);
}

template <class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(std::shared_ptr<BinaryNode<ItemType>> subTreePtr)
{
    //if we set the root to nullptr that should destroy the whole tree?
	if (subTreePtr)
	{
		destroyTree(subTreePtr->getLeftChildPtr());
		destroyTree(subTreePtr->getRightChildPtr());
		subTreePtr.reset();
	}
}

// PUBLIC BINARY_TREE_INTERFACE METHODS SECTION
template <class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const
{
	return !rootPtr;
}

template <class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const
{
	return getHeightHelper(rootPtr);
}

template <class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const
{
	if (subTreePtr) return 1 + std::max(getHeightHelper(subTreePtr->getLeftChildPtr()), getHeightHelper(subTreePtr->getRightChildPtr()));
	else return 0;
}

template <class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const
{
	return getNumberOfNodesHelper(rootPtr);
}

template <class ItemType>
int BinaryNodeTree<ItemType>:: getNumberOfNodesHelper(std::shared_ptr<BinaryNode<ItemType>> subTreePtr) const
{
        if (subTreePtr.get() != 0) return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
	else return 0;
}

template <class ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const throw(PrecondViolatedExcept)
{
        if (rootPtr.get() != 0) return rootPtr->getItem();
	else throw PrecondViolatedExcept("Root does not exist!");
}


template <class ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType& newData)
{
    rootPtr->setItem(newData);
}

// Adds an item to the tree
template <class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData)
{
        std::shared_ptr<BinaryNode<ItemType>> add = std::make_shared<BinaryNode<ItemType>>(newData);
	rootPtr = balancedAdd(rootPtr, add);
	return true;
}

template <class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::balancedAdd(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,std::shared_ptr<BinaryNode<ItemType>> newNodePtr)
{
        if (subTreePtr.get() != nullptr)
	{
		std::shared_ptr<BinaryNode<ItemType>> leftPtr = subTreePtr->getLeftChildPtr();
		std::shared_ptr<BinaryNode<ItemType>> rightPtr = subTreePtr->getRightChildPtr();

		if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
		{
			rightPtr = balancedAdd(rightPtr, newNodePtr);
			subTreePtr->setRightChildPtr(rightPtr);
		}
		else
		{
			leftPtr = balancedAdd(leftPtr, newNodePtr);
			subTreePtr->setLeftChildPtr(leftPtr);
		}
                return subTreePtr;
	}
	else
	{
		return newNodePtr;
	}
}

// Removes specified item from the tree
template <class ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& data)
{
	bool isSuccessful = false;
	rootPtr = removeValue(rootPtr, data, isSuccessful);
	return isSuccessful;
}

template <class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr, const ItemType target, bool& isSuccessful)
{
	/* 1. traverse tree looking for the item
	 * 2. if found, delete it and move values up tree
	 * 3. (use recursion to accomplish this)
	 *
	 */
	if (!subTreePtr)
	{
		isSuccessful = false;
	}
	else if (subTreePtr->getItem() == target)
	{
		subTreePtr = moveValuesUpTree(subTreePtr); //reassigning is an implicit deletion
		isSuccessful = true;
	}
	else
	{ //all values of the tree have to be searched
            bool leftSearch = false;
            std::shared_ptr<BinaryNode<ItemType>> tempLeft = removeValue(subTreePtr->getLeftChildPtr(), target, leftSearch);
            subTreePtr->setLeftChildPtr(tempLeft);
            //add early break case?
            bool rightSearch = false;
            std::shared_ptr<BinaryNode<ItemType>> tempRight = removeValue(subTreePtr->getRightChildPtr(), target, rightSearch);
            subTreePtr->setRightChildPtr(tempRight);

            isSuccessful = (leftSearch || rightSearch);
	}
	return subTreePtr;
}

template <class ItemType>
auto BinaryNodeTree<ItemType>::moveValuesUpTree(std::shared_ptr<BinaryNode<ItemType>> subTreePtr)
{
        //no children
        if (subTreePtr->isLeaf()) return  std::shared_ptr<BinaryNode<ItemType>>(nullptr);
        std::shared_ptr<BinaryNode<ItemType>> oldRight;
        if (subTreePtr->getRightChildPtr() && subTreePtr->getLeftChildPtr())
        { //2 children
            auto rightPtr = subTreePtr->getRightChildPtr();
            oldRight = rightPtr;
            return std::make_shared<BinaryNode<ItemType>>(oldRight->getItem(), subTreePtr->getLeftChildPtr(), moveValuesUpTree(rightPtr)); //cannot just return oldRight because that would destroy the left subtree of subTreePtr
	}
        else //1 child
        {
            if (subTreePtr->getRightChildPtr())
                return subTreePtr->getRightChildPtr();
            else
                return subTreePtr->getLeftChildPtr();
	}
}

template <class ItemType>
void BinaryNodeTree<ItemType>::clear()
{
	destroyTree(rootPtr);
        rootPtr = std::shared_ptr<BinaryNode<ItemType>>(nullptr);
}

template <class ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
	bool test;
        std::shared_ptr<BinaryNode<ItemType>> item = findNode(rootPtr, anEntry, test);
	if (item) return item->getItem();
	throw NotFoundException("Item not found!");
}

template <class ItemType>
bool BinaryNodeTree<ItemType>::contains(const ItemType& anEntry) const
{
	bool test;
	return findNode(rootPtr, anEntry, test).get() != 0;
}

template <class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNodeTree<ItemType>::findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr,const ItemType& target, bool& isSuccessful) const
{
	//isSuccessful has to be false***
	if (treePtr)
	{
		if (treePtr->getItem() == target)
		{
			isSuccessful = true;
			return treePtr;
		}
		else
		{
			std::shared_ptr<BinaryNode<ItemType>> searchRight = findNode(treePtr->getRightChildPtr(), target, isSuccessful);
			if (searchRight) return searchRight;
			std::shared_ptr<BinaryNode<ItemType>> searchLeft = findNode(treePtr->getLeftChildPtr(), target, isSuccessful);
			if (searchLeft) return searchLeft;
		}
	}
	return nullptr;
}

// PUBLIC TRAVERSAL SECTION
template <class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
	preorder(visit, rootPtr);
}

template <class ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const
{
	if (treePtr)
	{
		ItemType item = treePtr->getItem();
		visit(item);
		preorder(visit, treePtr->getLeftChildPtr());
		preorder(visit, treePtr->getRightChildPtr());
	}
}

template <class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
	inorder(visit, rootPtr);
}

template <class ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const
{
	if (treePtr)
	{
		inorder(visit, treePtr->getLeftChildPtr());
		ItemType item = treePtr->getItem();
		visit(item);
		inorder(visit, treePtr->getRightChildPtr());
	}
}

template <class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
	postorder(visit, rootPtr);
}


template <class ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType&), std::shared_ptr<BinaryNode<ItemType>> treePtr) const
{
	if (treePtr)
	{
		postorder(visit, treePtr->getLeftChildPtr());
		postorder(visit, treePtr->getRightChildPtr());
		ItemType item = treePtr->getItem();
		visit(item);
	}
}

// OVERLOADED OPERATOR SECTION
template <class ItemType>
BinaryNodeTree<ItemType>& BinaryNodeTree<ItemType>::operator= (const BinaryNodeTree& rightHandSide) //not sure if the argument needs a template as well
{
    if (this != &rightHandSide)
    {
	destroyTree(rootPtr);
	rootPtr = copyTree(rightHandSide.rootPtr);
    }
    return *this;
}
