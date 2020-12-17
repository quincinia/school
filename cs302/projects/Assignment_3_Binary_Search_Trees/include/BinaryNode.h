#ifndef BINARYNODE_H
#define BINARYNODE_H
#include <memory>

template<class ItemType>
class BinaryNode
{
    private:
        ItemType item; // Data portion
        std::shared_ptr<BinaryNode<ItemType>> leftChildPtr; // Pointer to left child
        std::shared_ptr<BinaryNode<ItemType>> rightChildPtr; // Pointer to right child
    public:
        BinaryNode();
        BinaryNode(const ItemType& anItem);
        BinaryNode(const ItemType& anItem,std::shared_ptr<BinaryNode<ItemType>> leftPtr,std::shared_ptr<BinaryNode<ItemType>> rightPtr);
        void setItem(const ItemType& anItem);
        ItemType getItem() const;
        bool isLeaf() const;
        auto getLeftChildPtr() const;
        auto getRightChildPtr() const;
        void setLeftChildPtr(std::shared_ptr<BinaryNode<ItemType>> leftPtr);
        void setRightChildPtr(std::shared_ptr<BinaryNode<ItemType>> rightPtr);
}; // end BinaryNode
#include "../src/BinaryNode.cpp"
#endif // BINARYNODE_H
