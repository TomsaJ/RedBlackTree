#include <iostream>
using namespace std;

template <typename T>
class RedBlackTree;

template <typename T>
class TreeNode
{
	friend class RedBlackTree<T>;

public:
	TreeNode* parent = nullptr;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;

	bool black = true;

public:
	const T key;
	//Constructor
	TreeNode(const T rootKey) : key(rootKey) {}
	// Destructor
	virtual ~TreeNode()
	{
		if (left != this)
		{
			delete left;
		}
		if (right != this)
		{
			delete right;
		}
	}

	TreeNode(const TreeNode& copyFrom) = delete;
	TreeNode(TreeNode&& moveFrom) = delete;

	friend std::ostream& operator<<(std::ostream& cout, const TreeNode* tree)
	{
		if (tree == nullptr)
			return cout;

		cout << tree->left << tree->key << ", " << tree->right;

		return cout;
	}

private:
	static TreeNode* search(TreeNode* root, const T key, TreeNode* nil);
};

template <typename T>
class RedBlackTree
{
	using Node = TreeNode<T>;

private:
	Node* root;
	Node* nil;

public:
	RedBlackTree();
	virtual ~RedBlackTree()
	{
		delete root;
		delete nil;
	}

	RedBlackTree(const RedBlackTree& copyFrom) = delete;
	RedBlackTree(RedBlackTree&& moveFrom) = delete;

public:
	void insert(const T key);
	Node* search(const T key);
	void insertFixup(Node* node);

	void print();

	void leftRotate(Node* node);

	void rightRotate(Node* node);

private:
	void printSubTree(Node* tree, int depth);

public:
	friend std::ostream& operator<<(std::ostream& cout, const RedBlackTree& tree)
	{
		cout << tree.root->left << "<" << tree.root->key << ">, " << tree.root->right; // markiert rootNode
		return cout;
	}
};

template <class T>
RedBlackTree<T>::RedBlackTree()
{
	nil = new Node(0);
	nil->parent = nullptr;
	nil->right = nullptr;
	nil->left = nullptr;
	nil->black = true;
	root = nil;
}

template <class T>
void RedBlackTree<T>::leftRotate(Node* node)
{
	if (node->right == nil)
		throw "Fehler beim left rotate";

	if (root->parent != nil)
		throw "Fehler beim left rotate";


	Node* y = node->right;
	node->right = y->left;

	if (y->left != nil)
		y->left->parent = node;

	y->parent = node->parent;
	if (node->parent == nil)
		root = y;

	else if (node == node->parent->left)
		node->parent->left = y;
	else
		node->parent->right = y;
	y->left = node;
	node->parent = y;
}

template <class T>
void RedBlackTree<T>::rightRotate(Node* node)
{
	if (node->left == nil)
		throw "Fehler beim right rotate";

	if (root->parent != nil)
		throw "Fehler beim right rotate";
	Node* y = node->left;
	node->left = y->right;

	if (y->right != nil)
		y->right->parent = node;

	y->parent = node->parent;
	if (node->parent == nil)
		root = y;

	else if (node == node->parent->right)
		node->parent->right = y;
	else
		node->parent->left = y;

	y->right = node;
	node->parent = y;
}

template <class T>
void RedBlackTree<T>::print()
{
	std::cout << "-----------------------------------------\n";
	printSubTree(root, 0);
	std::cout << "-----------------------------------------\n";
}

/*
 * Method to output from the tree
 * Works recursively
 */
template <class T>
void RedBlackTree<T>::printSubTree(Node* tree, int depth)
{
	if (tree == nil)
		return;
	printSubTree(tree->right, depth + 1);

	for (int i = 0; i < depth; i++)
	{
		std::cout << "     ";
	}
	std::cout << "(" << tree->key;
	if (tree->black == true)
	{
		cout << "Black";
	}
	else
	{
		cout << "Red";
	}
	cout << ")"
		<< "\n";

	printSubTree(tree->left, depth + 1);

}

/*
 * Insert method
 * Inserts a node in the right place in the tree.
 * Finally, insert fixup is called
 */
template <class T>
void RedBlackTree<T>::insert(const T key)
{
	Node* z = new Node(key);
	Node* y = nil;
	Node* x = root;
	while (x != nil)
	{
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if (y == nil)
		root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;

	z->left = nil;
	z->right = nil;
	z->black = false;
	insertFixup(z);
}

/*
 * Insert_fixup method
 * The method is called in the method insert and ensures
 * Ensures that the tree is balanced even after the insert.
 * With the help of the different cases.
 */

template <class T>
void RedBlackTree<T>::insertFixup(Node* z)
{
	Node* y = nil;
	while (z->parent->black == false)
	{
		if (z->parent == z->parent->parent->left)
		{
			y = z->parent->parent->right;
			if (y->black == false)
			{
				z->parent->black = true;
				y->black = true;
				z->parent->parent->black = false;
				z = z->parent->parent;
			}
			else if (z == z->parent->right)
			{
				z = z->parent;
				leftRotate(z);
			}
			else
			{
				z->parent->black = true;
				z->parent->parent->black = false;
				rightRotate(z->parent->parent);
			}
		}
		else
		{
			y = z->parent->parent->left;
			if (y->black == false)
			{
				z->parent->black = true;
				y->black = true;
				z->parent->parent->black = false;
				z = z->parent->parent;
			}
			else if (z == z->parent->left)
			{
				z = z->parent;
				rightRotate(z);
			}
			else
			{
				z->parent->black = true;
				z->parent->parent->black = false;
				leftRotate(z->parent->parent);
			}
		}
	}

	root->black = true;
}

/*
 * Function search of the class Searchtree calls the function search of the class TreeNode
 */
template <class T>
TreeNode<T>* RedBlackTree<T>::search(const T key)
{
	return TreeNode<T>::search(root, key, nil);
}

/*
 * function of the TreeNode class gets the pointer to the node with the
 * searched key value.
 * The function is passed a pointer to the root, the key value being searched for, and a 
 * pointer to nil.
 */
template <class T>
TreeNode<T>* TreeNode<T>::search(TreeNode* root, const T key, TreeNode* nil)
{
	if (root == nil)
		return nullptr;
	if (key == root->key)
		return root;
	if (key < root->key)
		return TreeNode<T>::search(root->left, key, nil);
	else
		return TreeNode<T>::search(root->right, key, nil);
}
