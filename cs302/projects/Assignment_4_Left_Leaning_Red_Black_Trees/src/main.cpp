#include <iostream>
#include <ctime>
#include <cstdlib>
#include <RedBlackNode.h>
#include <LLRB_T.h>
#include "RedBlackNode.cpp"
#include "LLRB_T.cpp"
using namespace std;

int main()
{
	srand(time(0));
	LLRB_T<int> tree;
	int inputs[15] = {89, 96, 52, 66, 59, 69, 37, 6, 54, 15};

	for (int i = 0; i < 14; ++i)
	{
		int gen = rand() % 31; //just choosing some arbitrary limit
		//gen = inputs[i]; //uncomment to test custom input
		while (tree.contains(gen))
			gen = rand() % 31;
		tree.insert(gen);
		tree.printNode(gen);
		tree.printParent(gen);
		cout << endl;
		inputs[i] = gen;
	}
	cout << "(Inorder) Tree before removal:" << endl;
	tree.traverse();
	tree.remove(inputs[3]);
	cout << "\n(Inorder) Tree after removal:" << endl;
	tree.traverse();
	return 0;
}
