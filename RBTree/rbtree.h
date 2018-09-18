class RBNode {
public:
	static const int RED = 0;
	static const int BLACK = 1;
	int key;
	int color;
	RBNode *left;
	RBNode *right;
	RBNode *p;
};

class RBTree {
public:
	RBNode *root;
	RBNode *nil;
	RBTree() {
		nil = new RBNode;
		nil->left = nil->right = nil->p = nil;
		nil->key = 0;
		nil->color = RBNode::BLACK;
		root = nil;
	}

	RBNode* search(int key);
	RBNode* minimum(RBNode* cur);
	RBNode* maximum(RBNode* cur);
	RBNode* successor(RBNode* cur);
	RBNode* predecessor(RBNode* cur);
	void left_rotate(RBNode* z);
	void right_rotate(RBNode* z);

	void insert_fixup(RBNode* z);
	bool insert(int key); // true if inserted, false if already exist -> not inserted

	void transplant(RBNode* u, RBNode* v);
	void erase_fixup(RBNode* z);
	bool erase(int key);
};