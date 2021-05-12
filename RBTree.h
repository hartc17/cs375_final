class RBTree {
	public:
		void rotateLeft(Node *&rot, Node *&pt);
		void rotateRight(Node *&root, Node *&pt);
		void fixViolation(Node *&root, Node *&pt);
		void insert(const int &data);
		void inorder();
		void levelOrder();
};
