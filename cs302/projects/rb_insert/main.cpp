#include <iostream>
#include <algorithm> //swap
using namespace std;

struct Node
{
	int data;
	bool isRed;
	Node* left;
	Node* right;
	Node* parent;

	Node(int data)
		: data(data),
		  isRed(true),
		  left(nullptr),
		  right(nullptr),
		  parent(nullptr)
	{}
};

class RBTree
{
	private:
		Node* root;
	protected:
		void rotateLeft(Node*&, Node*&);
		void rotateRight(Node*&, Node*&);
		void fixUp(Node*&, Node*&);
	public:
		RBTree() : root(nullptr) {}
		void insert(const int& n);

		//probably not gonna use
		void inorder();
		void levelOrder();
};

void inorderHelper(Node* root)
{
	if (root == nullptr) return;
	inorderHelper(root->left);
	cout << root->data << " ";
	inorderHelper(root->right);
}

void RBTree::inorder()
{
	inorderHelper(root);
}

void levelOrderHelper(Node* root);

//correctly place the new node and fix parent structure
Node* insertRec(Node* root, Node* newNode)
{
	//if the tree is empty, the new node is the root
	if (root == nullptr)
		return newNode;

	//recurse down the tree until you place the node
	if (newNode->data < root->data)
	{
		root->left = insertRec(root->left, newNode);
		root->left->parent = root;
	}
	else if (newNode->data > root->data)
	{
		root->right = insertRec(root->right, newNode);
		root->right->parent = root;
	}

	return root;
}

void RBTree::rotateLeft(Node*& root, Node*& axis)
{
	Node* ax_right = axis->right;

	//right child's left subtree becomes the axis's right subtree
	axis->right = ax_right->left;

	if (axis->right != nullptr)
		axis->right->parent = axis;

	//right child takes axis's spot
	ax_right->parent = axis->parent;

	if (axis->parent == nullptr)
		root = ax_right;

	else if (axis == axis->parent->left)
		axis->parent->left = ax_right;

	else
		axis->parent->right = ax_right;

	//axis is now the left child of its (old) right child
	ax_right->left = axis;

	//old right child becomes the parent
	axis->parent = ax_right;
}

//symmetric version of rotateLeft
void RBTree::rotateRight(Node*& root, Node*& axis)
{
	Node* ax_left = axis->left;
	axis->left = ax_left->right;

	if (axis->left != nullptr)
		axis->left->parent = axis;

	ax_left->parent = axis->parent;

	if (axis->parent == nullptr)
		root = ax_left;

	else if (axis == axis->parent->left)
		axis->parent->left = ax_left;

	else
		axis->parent->right = ax_left;

	ax_left->right = axis;
	axis->parent = ax_left;
}

void RBTree::fixUp(Node*& root, Node*& curr)
{
	Node* parent_pt = nullptr;
	Node* grandparent_pt = nullptr;

	while ((curr != root) &&
		   (!curr->isRed) &&
		   (curr->parent->isRed))
	{
		parent_pt = curr->parent;
		grandparent_pt = curr->parent->parent;

		//Case A:
		//curr is a left grandchild
		if (parent_pt == grandparent_pt->left)
		{
			Node* uncle_pt = grandparent_pt->right;

			//Case 1:
			//item is added to 4-node
			//fix: perform a color flip
			if (uncle_pt != nullptr && uncle_pt->isRed)
			{
				grandparent_pt->isRed = true;
				parent_pt->isRed = false;
				uncle_pt->isRed = false;

				//grandparent gets bubbled up,
				//fix any issues this makes
				curr = grandparent_pt;
			}
			else
			{
				//Case 2:
				//red node added to red side of 3-node
				//curr is right child
				//fix: left-rotation
				if (curr == parent_pt->right)
				{
					rotateLeft(root, parent_pt);

					//move up tree
					curr = parent_pt;
					parent_pt = curr->parent;
				}

				//Case 3:
				//same as above except curr is left child
				//fix: right-rotation
				rotateRight(root, grandparent_pt);
				swap(parent_pt->isRed, grandparent_pt->isRed);
				curr = parent_pt;
			}
		}

		//Case B:
		//symmetric cases of A
		else
		{
			Node* uncle_pt = grandparent_pt->left;

			if ((uncle_pt != nullptr) && (uncle_pt->isRed))
			{
				grandparent_pt->isRed = true;
				parent_pt->isRed = false;
				uncle_pt->isRed = false;
				curr = grandparent_pt;
			}
			else
			{
				if (curr == parent_pt->left)
				{
					rotateRight(root, parent_pt);
					curr = parent_pt;
					parent_pt = curr->parent;
				}

				rotateLeft(root, grandparent_pt);
				swap(parent_pt->isRed, grandparent_pt->isRed);
				curr = parent_pt;
			}
		}
	}
	root->isRed = false;
}

void RBTree::insert(const int &n)
{
	Node* newNode = new Node(n);
	root = insertRec(root, newNode);
	fixUp(root, newNode);
}

int main()
{
	RBTree tree;
	tree.insert(7);
	tree.insert(6);
	tree.insert(5);
	tree.insert(4);
	tree.insert(3);
	tree.insert(2);
	tree.insert(1);

	cout << "Inoder Traversal of Created Tree\n";
	tree.inorder();
	cout << endl;

	return 0;
}
