template<typename T>
void SearchTree<T>::rotateLeft(Node* x) {
	Node* y = x->right;
	x->right = y->left;

	if(y->left != nil)
		y->left->parent = x;
	y->parent = x->parent;

	if(x->parent == nil)
		root = y;
	else if(x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}

template<typename T>
void SearchTree<T>::rotateRight(Node* x) {
	Node* y = x->left;
	x->left = y->right;

	if(y->right != nil)
		y->right->parent = x;
	y->parent = x->parent;

	if(x->parent == nil)
		root = y;
	else if(x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;

	y->right = x;
	x->parent = y;
}

template<typename T>
void SearchTree<T>::insert(const T key) {
	Node *const newNode = new Node(key); // "z"

	Node *aboveNew = nil; // Node under which newNode will be inserted ("y")

	for (Node *x = root; x != nil; ) {
		aboveNew = x;

		if (newNode->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	newNode->parent = aboveNew; // adjust newNode's paret pointer

	if (aboveNew == nil)
		root = newNode;
	else if (newNode->key < aboveNew->key)
		aboveNew->left = newNode; // Insert newNode
	else
		aboveNew->right = newNode; // Insert newNode

	newNode->left = nil;
	newNode->right = nil;
	newNode->color = Node::RED;

	insertFixup(newNode);
}

template<typename T>
void SearchTree<T>::insertFixup(Node* z) {
	// RB-Insert-Fixup(T, z)
	while (z->parent->color == Node::RED) {
		if (z->parent == z->parent->parent->left) {
			Node* y = z->parent->parent->right;
			if (y->color == Node::RED) {
				z->parent->color = Node::BLACK; // Fall 1
				y->color = Node::BLACK; // Fall 1
				z->parent->parent->color = Node::RED; // Fall 1
				z = z->parent->parent; // Fall 1
			} else {
				if (z == z->parent->right) {
					z = z->parent; // Fall 2
					rotateLeft(z); // Fall 2
				}
				z->parent->color = Node::BLACK; // Fall 3
				z->parent->parent->color = Node::RED; // Fall 3
				rotateRight(z->parent->parent); // Fall 3
			}
		} else { // (analog zum then-Fall, nur “right” und “left” vertauschen)
			if (z->parent == z->parent->parent->right) {
				Node* y = z->parent->parent->left;
				if (y->color == Node::RED) {
					z->parent->color = Node::BLACK; // Fall 1
					y->color = Node::BLACK; // Fall 1
					z->parent->parent->color = Node::RED; // Fall 1
					z = z->parent->parent; // Fall 1
				} else {
					if (z == z->parent->left) {
						z = z->parent; // Fall 2
						rotateRight(z); // Fall 2
					}
					z->parent->color = Node::BLACK; // Fall 3
					z->parent->parent->color = Node::RED; // Fall 3
					rotateLeft(z->parent->parent); // Fall 3
				}
			}
		}
	}
	root->color = Node::BLACK;
}

template<typename T>
TreeNode<T>* SearchTree<T>::search(const T key) {
	const auto search_ = [&](const auto search, Node *root, const T key) -> Node* {
		if(root == nil)
			// return nil;
			return nullptr;

		if(key == root->key)
			return root;

		if(key < root->key)
			return search(search, root->left, key);

		return search(search, root->right, key);
	};

	return search_(search_, root, key);
}

