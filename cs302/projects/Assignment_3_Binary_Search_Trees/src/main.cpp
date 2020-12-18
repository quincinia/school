#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <utility> //swap
#include <BinarySearchTree.h>
using namespace std;

template <class ItemType>
void print(ItemType& item)
{
	cout << item << "\t";
}

ofstream output("output.txt"); //no other way to print to file without modifying the class

template <class ItemType>
void printfile(ItemType& item)
{
	output << item << "\t";
}


int main()
{
	srand(time(0));
	int DATA_SET_SIZE = 100; //for debugging purposes

	int values[200];
	int data[DATA_SET_SIZE];
	BinarySearchTree<int> tree2;
	for (int i = 0; i < 200; ++i) values[i] = i+1;
	for (int i = 0; i < DATA_SET_SIZE; ++i)
	{
		int& gen = values[rand() % (200-i)];
		tree2.add(gen);
		data[i] = gen;
		swap(gen, values[199-i]);
	}

	cout << "Input data:" << endl;
	output << "Input data:" << endl;
	for (int i = 0; i < DATA_SET_SIZE; ++i)
	{
		cout << data[i] << "\t"; //display input set
		output << data[i] << "\t";
	}

	cout << "\nHeight:" << tree2.getHeight() << endl; //display height
	output << "\nHeight:" << tree2.getHeight() << endl;

	//inorder
	cout << "Inorder:" << endl;
	output << "Inorder:" << endl;
	tree2.inorderTraverse(print);
	cout << endl;
	tree2.inorderTraverse(printfile);
	output << endl;

	//preorder
	cout << "Preorder:" << endl;
	output << "Preorder:" << endl;
	tree2.preorderTraverse(print);
	cout << endl;
	tree2.preorderTraverse(printfile);
	output << endl;

	//postorder
	cout << "Postorder:" << endl;
	output << "Postorder:" << endl;
	tree2.postorderTraverse(print);
	cout << endl;
	tree2.postorderTraverse(printfile);
	output << endl;

	//debugging
	cout << "\nTesting NodeTree Functions..." << endl;
	shared_ptr<BinaryNodeTree<int>> test1 = make_shared<BinaryNodeTree<int>>(); //copy ctor, tests copyTree
	for (int i = 0; i < DATA_SET_SIZE; ++i)
	{
		test1->add(data[i]);
	}
	cout << "Testing known removal..." << endl;
	cout << "Nodes before removal: " << test1->getNumberOfNodes() << endl;
	cout << test1->remove(data[0]) << endl;
	cout << "Nodes after removal: " << test1->getNumberOfNodes() << endl;

	cout << "New height: " << test1->getHeight() << endl;
	cout << "New root: " << test1->getRootData() << endl;
	//maybe print new tree?

	test1->add(data[0]);
	//print new tree

	cout << "Testing unknown remove: " << test1->remove(-1) << endl;
	cout << "Testing known entry: " << test1->getEntry(data[DATA_SET_SIZE-2]) << endl; //testing a far value so that the recursion is used
	try {
		cout << "Testing unknown entry...";
		test1->getEntry(-1);
		cout << "found" << endl;
	} catch (NotFoundException) {
		cout << "not found" << endl;
	}

	cout << "Testing empty: " << test1->isEmpty() << endl;
	cout << "Testing clear: ";
	test1->clear();
	cout << test1->isEmpty() << endl;
	cout << "Number of nodes: " << test1->getNumberOfNodes() << endl;
	BinaryNodeTree<int> param(-1);


	cout << "\nTesting BST Functions..." << endl;
	BinarySearchTree<int> param2(-1);
	BinarySearchTree<int> test2;
	test2 = tree2;
	cout << "Number of nodes: " << test2.getNumberOfNodes() << endl;
	cout << "Testing known removal: " << test2.remove(data[0]) << endl;
	cout << "Number of nodes: " << test2.getNumberOfNodes() << endl;
	cout << "New root: " << test2.getRootData() << endl;
	cout << "Testing unknown removal: " << test2.remove(-1) << endl;
	cout << "Testing known entry: " << test2.getEntry(data[DATA_SET_SIZE-2]) << endl; //testing a far value so that the recursion is used
	try {
		cout << "Testing unknown entry...";
		test2.getEntry(-1);
		cout << "found" << endl;
	} catch (NotFoundException) {
		cout << "not found" << endl;
	}
	return 0;
}
