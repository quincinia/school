#include <BinarySearchTree.h>

template <class ItemType>
auto BinarySearchTree<ItemType>::placeNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,std::shared_ptr<BinaryNode<ItemType>> newNode)
{
	std::shared_ptr<BinaryNode<ItemType>> temp;
	if (!subTreePtr)
		return newNode;
	else if (subTreePtr->getItem() > newNode->getItem())
	{
		temp = placeNode(subTreePtr->getLeftChildPtr(), newNode);
		subTreePtr->setLeftChildPtr(temp);
	}
	else
	{
		temp = placeNode(subTreePtr->getRightChildPtr(), newNode);
		subTreePtr->setRightChildPtr(temp);
	}
	return subTreePtr;
}

template <class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,const ItemType target, bool& isSuccessful)
{
	std::shared_ptr<BinaryNode<ItemType>> temp;
	if (!subTreePtr)
	{
		isSuccessful = false;
	}
	else if (subTreePtr->getItem() == target)
	{
		//if the item exists, remove it
		subTreePtr = removeNode(subTreePtr);
		isSuccessful = true;
	}
	else if (subTreePtr->getItem() > target)
	{
		//search subtrees
		temp = removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful); //if a value is removed, reattach the new subtree
		subTreePtr->setLeftChildPtr(temp);
	}
	else
	{
		temp = removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful);
		subTreePtr->setRightChildPtr(temp);
	}
	return subTreePtr; //returns the updated node (or the node itself if no meaningful changes were made) (or nullptr if we reach the end)
}

template <class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr)
{
	std::shared_ptr<BinaryNode<ItemType>> temp;
        if (nodePtr->isLeaf()) //no children (leaf)
	{
                nodePtr = std::shared_ptr<BinaryNode<ItemType>>(nullptr); //implicit deletion
		return nodePtr;
	}
	else if (nodePtr->getLeftChildPtr() && nodePtr->getRightChildPtr()) //has 2 children
	{
		ItemType newItem;
		temp = removeLeftmostNode(nodePtr->getRightChildPtr(), newItem);
		nodePtr->setRightChildPtr(temp);
		nodePtr->setItem(newItem);
                return nodePtr;
	}
	else //has 1 child
	{
		if (nodePtr->getLeftChildPtr())
			temp = nodePtr->getLeftChildPtr();
		else
			temp = nodePtr->getRightChildPtr();
		return temp;
	}
}

template <class ItemType>
auto  BinarySearchTree<ItemType>::removeLeftmostNode(std::shared_ptr<BinaryNode<ItemType>>subTreePtr,ItemType& inorderSuccessor)
{
	std::shared_ptr<BinaryNode<ItemType>> temp;
        if (!(subTreePtr->getLeftChildPtr())) //has no left child
	{
		inorderSuccessor = subTreePtr->getItem();
		return removeNode(subTreePtr);
	}
	else
	{
		temp = removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor);
		subTreePtr->setLeftChildPtr(temp);
		return subTreePtr;
	}
}

template <class ItemType>
auto BinarySearchTree<ItemType>::findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr,const ItemType& target) const
{
	if (!treePtr)
                return std::shared_ptr<BinaryNode<ItemType>>(nullptr);
	else if (treePtr->getItem() == target)
		return treePtr;
	else if (treePtr->getItem() > target)
		return findNode(treePtr->getLeftChildPtr(), target);
	else
		return findNode(treePtr->getRightChildPtr(), target);
}


template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree()
{
	//should already set root to null
}

template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem)
    : rootPtr(std::make_shared<BinaryNode<ItemType>>(rootItem, nullptr, nullptr))
{

}

template <class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& tree)
{
	rootPtr = copyTree(tree.rootPtr);
}

template <class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree()
{
        BinaryNodeTree<ItemType>::destroyTree(rootPtr);
}

template <class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
{
	return !rootPtr;
}

template <class ItemType>
int BinarySearchTree<ItemType>::getHeight() const
{
        return BinaryNodeTree<ItemType>::getHeightHelper(rootPtr);
}

template <class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const
{
        return BinaryNodeTree<ItemType>::getNumberOfNodesHelper(rootPtr);
}

template <class ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const throw(PrecondViolatedExcept)
{
        if (rootPtr) return rootPtr->getItem();
	else throw PrecondViolatedExcept("Root does not exist!");
}


template <class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType& newData)
{

}

template <class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newEntry)
{
	std::shared_ptr<BinaryNode<ItemType>> newNode = std::make_shared<BinaryNode<ItemType>>(newEntry);
	rootPtr = placeNode(rootPtr, newNode);
	return true;
}

template <class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& target)
{
    bool isSuccessful = false;
    rootPtr = removeValue(rootPtr, target, isSuccessful);
    return isSuccessful;
}

template <class ItemType>
void BinarySearchTree<ItemType>::clear()
{
        BinaryNodeTree<ItemType>::destroyTree(rootPtr);
}

template <class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
        std::shared_ptr<BinaryNode<ItemType>> item = findNode(rootPtr, anEntry);
	if (item) return item->getItem();
	throw NotFoundException("Item not found!");
}

template <class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const
{
    bool test;
        return (BinaryNodeTree<ItemType>::findNode(rootPtr, anEntry, test)).get() != 0;
}

template <class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
        BinaryNodeTree<ItemType>::preorder(visit, rootPtr);
}

template <class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
        BinaryNodeTree<ItemType>::inorder(visit, rootPtr);
}

template <class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
        BinaryNodeTree<ItemType>::postorder(visit, rootPtr);
}

template <class ItemType>
BinarySearchTree<ItemType>& BinarySearchTree<ItemType>::operator=(const BinarySearchTree<ItemType>& rightHandSide)
{
    if (this != &rightHandSide)
    {
        BinaryNodeTree<ItemType>::destroyTree(rootPtr);
        rootPtr = BinaryNodeTree<ItemType>::copyTree(rightHandSide.rootPtr);
    }
    return *this;
}





