#include <StackLinked.h>

template <typename DataType>
StackLinked<DataType>::StackLinked(int)
	: top(nullptr)
{
	//the int isn't really used for anything(?)
}

template <typename DataType>
void StackLinked<DataType>::deepCopy(StackNode * curr)
{
	if (curr->next != nullptr)
		deepCopy(curr->next);
	push(curr->dataItem);
}

template <typename DataType>
StackLinked<DataType>::StackLinked(const StackLinked<DataType>& other)
	: top(nullptr)
{
	deepCopy(other.top);
}


template <typename DataType>
StackLinked<DataType>& StackLinked<DataType>::operator=(const StackLinked<DataType>& other)
{
	if (this != &other) {
		if (!isEmpty())
				clear();
		deepCopy(other.top);
	}
	return *this;
}


template <typename DataType>
StackLinked<DataType>::~StackLinked()
{
	clear();
}


template <typename DataType>
void StackLinked<DataType>::push(const DataType& newDataItem) throw (std::logic_error)
{
	//linked list stack has no reason to throw error here, assuming it is a remnant from when the StackArray file was copied
	//maybe include try
	top = new StackNode(newDataItem, top);
}

template <typename DataType>
DataType StackLinked<DataType>::pop() throw (logic_error)
{
	if (isEmpty())
			throw logic_error("error: nothing to pop\n");

	StackNode * temp = top->next;
	DataType popped_item = top->dataItem;
	delete top;
	top = temp;
	return popped_item;
}

template <typename DataType>
void StackLinked<DataType>::clear()
{
	while (top != nullptr)
		pop();
}

template <typename DataType>
bool StackLinked<DataType>::isEmpty() const
{
	return top == nullptr;
}

template <typename DataType>
bool StackLinked<DataType>::isFull() const
{
	return 0;
	//pointer stacks can never be full?
}

template <typename DataType>
void StackLinked<DataType>::showStructure() const

// Linked list implementation. Outputs the data elements in a stack.
// If the stack is empty, outputs "Empty stack". This operation is
// intended for testing and debugging purposes only.

{
	if( isEmpty() )
	{
	cout << "Empty stack" << endl;
	}
	else
	{
		cout << "Top\t";
	for (StackNode* temp = top; temp != 0; temp = temp->next) {
		if( temp == top ) {
		cout << "[" << temp->dataItem << "]\t";
		}
		else {
		cout << temp->dataItem << "\t";
		}
	}
		cout << "Bottom" << endl;
	}

}

template <typename DataType>
bool StackLinked<DataType>::hasOne() const
{
	if (isEmpty()) return false;
	return (top->next == nullptr);
}
