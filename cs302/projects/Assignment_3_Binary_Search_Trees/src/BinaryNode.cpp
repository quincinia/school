#include <BinaryNode.h>

template <class ItemType>
BinaryNode<ItemType>::BinaryNode()
{
    //the shared pointers shoud already default to null?
}

template <class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem)
    : item(anItem)
{
    //again, don't need to do anything with the pointers
}

template <class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem,std::shared_ptr<BinaryNode<ItemType>> leftPtr,std::shared_ptr<BinaryNode<ItemType>> rightPtr)
    : item(anItem),
      leftChildPtr(leftPtr),
      rightChildPtr(rightPtr)
{

}

template <class ItemType>
void BinaryNode<ItemType>::setItem(const ItemType& anItem)
{
    item = anItem;
}

template <class ItemType>
ItemType BinaryNode<ItemType>::getItem() const
{
    return item;
}

template <class ItemType>
bool BinaryNode<ItemType>::isLeaf() const
{
    return (!leftChildPtr && !rightChildPtr);
    //true only if left and right children are not null (0)
}

template <class ItemType>
auto BinaryNode<ItemType>::getLeftChildPtr() const
{
    return leftChildPtr;
}

template <class ItemType>
auto BinaryNode<ItemType>::getRightChildPtr() const
{
    return rightChildPtr;
}

template <class ItemType>
void BinaryNode<ItemType>:: setLeftChildPtr(std::shared_ptr<BinaryNode<ItemType>> leftPtr)
{
    leftChildPtr = leftPtr;
}

template <class ItemType>
void BinaryNode<ItemType>::setRightChildPtr(std::shared_ptr<BinaryNode<ItemType>> rightPtr)
{
    rightChildPtr = rightPtr;
}
