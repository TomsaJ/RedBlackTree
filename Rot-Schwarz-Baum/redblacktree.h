#pragma once

#include <iostream>


template<typename T>
class SearchTree;


template<typename T>
class TreeNode 
{
	friend class SearchTree<T>;

public:
	TreeNode* parent = nullptr;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;

	
	
	enum Color {
		RED,
		BLACK
	} color = BLACK;



public:
	const T key;

public:
	TreeNode(const T key = -1) : key(key) {}
	/*virtual ~TreeNode() {
		if(left != this)
			delete left;
		if(right != this)
			delete right;
	}*/

	// Disallow (accidental) copying or moving:
	TreeNode(const TreeNode& copyFrom) = delete;
	TreeNode& operator=(const TreeNode& copyFrom) = delete;
	TreeNode(TreeNode&& moveFrom) = delete;
	TreeNode& operator=(TreeNode&& moveFrom) = delete;

public:
/*
TreeNode* predecessor()
    {
        if (this->left != nullptr)
            return this->left->maximum();
    }

    TreeNode* successor()
    {
        if (this->right != nullptr) 
        {
            return this->right->minimum();
        }
        else
        {
            throw 4;
        }
            
    }

    TreeNode* minimum()
    {
        TreeNode* x = this;
        while (x->left != nullptr)
            x = x->left;
        return x;
    }
    TreeNode* maximum()
    {
        TreeNode* x = this;
        while (x->right != nullptr)
            x = x -> right;
        return x;
    }
	*/

    TreeNode* search(T key)
    {
        if (this->key == key)             // wenn der schl�ssel gleich gro� ist
            return this;
        if (this->key > key)               // wenn der schl�ssel kleiner ist
        {
            if (left == nullptr)     // wenn linker pointer null ist dann den linken ausgeben
                return left;
            return left->search(key);
        }
        else
        {
            if (right == nullptr)        // ansonsten den rechten zweig ausgeben
                return right;
            return right->search(key);
        }
    }


public:
	// optional, aber praktisch zum debuggen:
	friend std::ostream& operator<<(std::ostream& cout, const TreeNode* tree) {
		if(tree == nullptr) return cout; // nothing to print

		cout << tree->left << tree->key << ", " << tree->right;

		return cout;
	}
};


template<typename T>
class SearchTree 
{
	using Node = TreeNode<T>; // optional, Fuer uebersichtlichen Code

private:
	Node* nil; // NIL element (existiert immer)
	Node* root; // Wurzel (im Falle eines leeren Baumes: nil)

public:
	SearchTree(): nil(new Node) { root = nil; }
	virtual ~RBSearchTree() {
		Node* now = root;
		while (now != nil) {
			if (now->left != nil) {
				now = now->left;
			}
			else if (now->right != nil) {
				now = now->right;
			}
			else {
				Node* next = now->parent;
                if (next != nil) {
                    if(next->left == now)
                        next->left = nil;
                    if(next->right == now)
                        next->right = nil;
				}
				delete now;
				now = next;
			}
		}
		delete nil;
	}

	// Disallow (accidental) copying or moving:
	SearchTree(const SearchTree& copyFrom) = delete;
	SearchTree& operator=(const SearchTree& copyFrom) = delete;
	SearchTree(SearchTree&& moveFrom) = delete;
	SearchTree& operator=(SearchTree&& moveFrom) = delete;

private:
	// void transplant(const Node *const nodeToReplace, Node *const replacementNode); // internally used by void delete_node(...)

public:
	void rotateLeft(Node* x);
	void rotateRight(Node* x);
	void insert(const T key);
	void insertFixup(Node* z);
	// void deleteNode(Node *const node); // "const Node *const node" nicht zulaessig, da node sonst nicht korrekt geloescht werden koennte
	Node* search(const T key);

	// Node* minimum() { return root->minimum(); }
	// Node* maximum() { return root->maximum(); }

public:
	// optional, aber praktisch zum debuggen:
	friend std::ostream& operator<<(std::ostream& cout, const SearchTree& tree) {
		const auto printSub = [&](const auto& printSub, const Node* node){
			if(node == tree.nil) return;
			cout << "(";
			printSub(printSub, node->left);
			// cout << " <- ";
			cout << " ";
			cout << node->key;
			cout << " ";
			// cout << " -> ";
			printSub(printSub, node->right);
			cout << ")";
		};

		printSub(printSub, tree.root); // markiert rootNode
		return cout;
	}


	void printSubtree(const Node* subTree, const size_t depth) const {
		if(subTree == nil) return;

		for(size_t i = 0; i < depth; i++)
			std::cout << "  ";
		std::cout << subTree->key << "\n";

		printSubtree(subTree->right, depth + 1);

		printSubtree(subTree->left, depth + 1);
	}

	// preorder-print:
	void print() const {
		printSubtree(root, 0);
	}

	bool isEmpty() const {
		return root == nil;
	}
};
