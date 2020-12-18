#include <StackArray.h>
//gonna mostly be following the 3.3 slides, maybe changing if needed
template <typename DataType>
StackArray<DataType>::StackArray(int maxNumber)
	: maxSize(maxNumber), top(-1), dataItems(new DataType[maxNumber])
{
	//not sure if we should be putting checks for negative sizes
	//top represents the true top, not the spot after
}

template <typename DataType>
StackArray<DataType>::StackArray(const StackArray& other)
	: top(other.top), dataItems(new DataType[other.maxSize])
{
	for (int i = 0; i <= other.top; ++i)
		dataItems[i] = other.dataItems[i];
}

template <typename DataType>
StackArray<DataType>& StackArray<DataType>::operator=(const StackArray& other)
{
	//fix this so that the array will physically change size to match that of the other array

	if (this != &other) {
		delete[] dataItems;
		dataItems = new DataType[other.maxSize];
		for (int i = 0; i <= other.top; ++i)
			dataItems[i] = other.dataItems[i];
		maxSize = other.maxSize;
		top = other.top;
	}
	return *this;
}

template <typename DataType>
StackArray<DataType>::~StackArray<DataType>()
{
	delete[] dataItems;
}

template <typename DataType>
void StackArray<DataType>::push(const DataType& newDataItem) throw (logic_error)
{
	if (!isFull()) {
		++top;
		dataItems[top] = newDataItem;
	} else {
		throw logic_error("Stack full, cannot push");
	}
}

template <typename DataType>
DataType StackArray<DataType>::pop() throw (logic_error)
{
	if (!isEmpty()) {
		return dataItems[top--];
	}
	throw logic_error("Empty stack, cannot pop");
}

template <typename DataType>
void StackArray<DataType>::clear()
{
	top = -1;
}

template <typename DataType>
bool StackArray<DataType>::isEmpty() const
{
	return top == -1;
}

template <typename DataType>
bool StackArray<DataType>::isFull() const
{
	return top == maxSize-1;
}

template <typename DataType>
void StackArray<DataType>::showStructure() const

// Array implementation. Outputs the data items in a stack. If the
// stack is empty, outputs "Empty stack". This operation is intended
// for testing and debugging purposes only.

{
	if( isEmpty() ) {
	cout << "Empty stack." << endl;
	}
	else {
	int j;
	cout << "Top = " << top << endl;
	for ( j = 0 ; j < maxSize ; j++ )
		cout << j << "\t";
	cout << endl;
	for ( j = 0 ; j <= top  ; j++ )
	{
		if( j == top )
		{
			cout << '[' << dataItems[j] << ']'<< "\t"; // Identify top
		}
		else
		{
		cout << dataItems[j] << "\t";
		}
	}
	cout << endl;
	}
	cout << endl;
}

template <typename DataType>
bool StackArray<DataType>::hasOne() const
{
	return top == 0;
}
