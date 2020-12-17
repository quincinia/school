#include <iostream>
#include <cmath>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode
{
	int val;
	TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
	TreeNode* left;
	TreeNode* right;
};

void treeTraversal(TreeNode* root)
{
	if (root)
	{
		cout << root->val << ", ";
		treeTraversal(root->left);
		treeTraversal(root->right);
	}
}

//where depth starts at 0
//the leaves of the tree are labeled from 0 to 2^d - 1
bool existLeaf(TreeNode* root, int depth, int id)
{
	int i = 0;
	int lo = 0;
	int hi = pow(2, depth) - 1;
	while (i < depth)
	{
		double side = ((double)id-lo) / (hi-lo);
		if (side < 0.5)
		{
			root = root->left;
			hi = lo + (hi-lo)/2;
		}
		else
		{
			root = root->right;
			lo = lo + (hi-lo)/2 + 1;
		}
		++i;
	}
	return (root != nullptr);
}

int countNodes(TreeNode* root)
{
	if (root == nullptr) return 0;
	TreeNode* curr = root;

	//we want depth to start counting from 0
	int depth = -1;
	while (curr != nullptr)
	{
		++depth;
		curr = curr->left;
	}
	cout << "Depth: " << depth << endl;

	//search bottom row
	int lo = 0;
	int hi = pow(2, depth) - 1;
	while (lo <= hi)
	{
		int id = lo + (hi-lo)/2;
		if (existLeaf(root, depth, id))
			lo = id + 1;
		else
			hi = id - 1;
	}

	//at the end of the while loop, lo will be the # of
	//nodes in the bottom row
	//# of nodes = # of nodes above the bottom row
	//			 + # of nodes in the bottom row
	return ((pow(2, depth)-1) + lo);
}

void buildCompleteTree(vector<int>& data, TreeNode*& root)
{
	queue<TreeNode*> q;
	q.push(root);
	for (int i = 0; i < data.size(); ++i)
	{
		//use a queue so that nodes at a lower depth are
		//"filled" first before nodes at a higher depth
		TreeNode* node = q.front();
		q.pop();
		node->val = data[i];

		//prep more (left) nodes if possible
		if (i + q.size() + 1 < data.size())
		{
			node->left = new TreeNode(0);
			q.push(node->left);
		}

		//prep more (right) nodes if possible
		if (i + q.size() + 1 < data.size())
		{
			node->right = new TreeNode(0);
			q.push(node->right);
		}
	}
	treeTraversal(root);
}
int main()
{
	vector<int> data = {1, 2, 3, 4};
	TreeNode* root = new TreeNode(0);
	buildCompleteTree(data, root);

	int res = countNodes(root);
	cout << "Total node: " << res << endl;
	return 0;
}
