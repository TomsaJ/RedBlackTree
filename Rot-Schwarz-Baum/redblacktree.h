#include <iostream>
#include <string>

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
	// Konstruktor
	TreeNode(const T rootKey) : key(rootKey) {}
	// Destruktor
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

	// Disallow (accidental) copying or moving:
	TreeNode(const TreeNode& copyFrom) = delete;
	TreeNode(TreeNode&& moveFrom) = delete;
	TreeNode* predecessor();
	TreeNode* successor();
	TreeNode* minimum();
	TreeNode* maximum();

	// optional, aber praktisch zum debuggen:
	friend std::ostream& operator<<(std::ostream& cout, const TreeNode* tree)
	{
		if (tree == nullptr)
			return cout; // nothing to print

		cout << tree->left << tree->key << ", " << tree->right;

		return cout;
	}

private:
	static TreeNode* search(TreeNode* root, const T key, TreeNode* nil);
};

template <class T>
TreeNode<T>* TreeNode<T>::predecessor()
{
	TreeNode* succ = this;
	TreeNode* desc = this;
	if (succ->left != nullptr)
		return succ->left->maximum();
	desc = succ->parent;
	while (desc != nullptr && succ == desc->left)
	{
		succ = desc;
		desc = desc->parent;
	}
	return desc;
}

template <class T>
TreeNode<T>* TreeNode<T>::successor()
{
	TreeNode* succ = this;
	TreeNode* desc = this;
	if (succ->right != nullptr)
		return succ->right->minimum();
	desc = succ->parent;
	while (desc != nullptr && succ == desc->right)
	{
		succ = desc;
		desc = desc->parent;
	}
	return desc;
}

/*template <class T>
TreeNode<T> *TreeNode<T>::minimum()
{
	TreeNode *min = this;
	while (min->left != nullptr)
		min = min->left;
	return min;
}

template <class T>
TreeNode<T> *TreeNode<T>::maximum()
{
	TreeNode *max = this;
	while (max->right != nullptr)
		max = max->right;
	return max;
}*/

template <typename T>
class RedBlackTree
{
	using Node = TreeNode<T>; // optional, Fuer uebersichtlichen Code

private:
	Node* root; // Wurzel (im Falle eines leeren Baumes: nullptr)
	Node* nil;

public:
	//SearchTree() : root(nullptr) {}
	RedBlackTree();
	virtual ~RedBlackTree() {
		delete root;
		delete nil;
	}

	// Disallow (accidental) copying or moving:
	RedBlackTree(const RedBlackTree& copyFrom) = delete;
	RedBlackTree(RedBlackTree&& moveFrom) = delete;

public:
	void insert(const T key);
	Node* search(const T key);
	void insert_fixup(Node* node);

	Node* minimum() { return root->minimum(); }
	Node* maximum() { return root->maximum(); }

	void print();

	void left_rotate(Node* node);

	void right_rotate(Node* node);


private:
	void printSubtree(Node* tree, int depth);

public:
	// optional, aber praktisch zum debuggen:
	friend std::ostream& operator<<(std::ostream& cout, const RedBlackTree& tree)
	{
		// cout << tree.root; // markiert rootNode nicht
		cout << tree.root->left << "<" << tree.root->key << ">, " << tree.root->right; // markiert rootNode
		return cout;
	}
};

template <class T>
RedBlackTree<T>::RedBlackTree() {
	nil = new Node(0);
	nil->parent = nullptr;
	nil->right = nullptr;
	nil->left = nullptr;
	nil->black = true;
	root = nil;
}

template <class T>
void RedBlackTree<T>::left_rotate(Node* node)
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
void RedBlackTree<T>::right_rotate(Node* node)
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
	printSubtree(root, 0);
	std::cout << "-----------------------------------------\n";
}

template <class T>
void RedBlackTree<T>::printSubtree(Node* tree, int depth)
{
	if (tree == nil)
		return;

	printSubtree(tree->right, depth + 1);

	for (int i = 0; i < depth; i++)
	{
		std::cout << "     ";
	}
	std::cout << "[" << tree->key << (tree->black == true ? "B" : "R")
		<< "]"
		<< "\n";

	printSubtree(tree->left, depth + 1);
}

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
	insert_fixup(z);
}
// TEST
template <class T>
void RedBlackTree<T>::insert_fixup(Node* z)
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
				left_rotate(z);
			}
			else {
				z->parent->black = true;
				z->parent->parent->black = false;
				right_rotate(z->parent->parent);
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
				right_rotate(z);
			}
			else {
				z->parent->black = true;
				z->parent->parent->black = false;
				left_rotate(z->parent->parent);
			}
		}
	}
	root->black = true;
}

template <class T>
TreeNode<T>* RedBlackTree<T>::search(const T key)
{
	return TreeNode<T>::search(root, key, nil);
}

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
