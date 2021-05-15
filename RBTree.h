#ifndef __RBTREE_H__
#define __RBTREE_H__

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


#define RED_NODE        false    
#define BLACK_NODE      true    


#define NODE_SET_PARENT(node, parent_node)  do { NODE_PARENT(node) = (parent_node); } while (0) //设置父亲接结点

template<typename RBTREE_DATA>
class RBTree {
public:
	struct RBTREE_NODE {
		RBTREE_DATA   data;
		bool color;
		RBTREE_NODE* left_node;
		RBTREE_NODE* right_node;
		RBTREE_NODE* parent_node;
	};


private:
	
	RBTREE_NODE* getParent(RBTREE_NODE* node);
	void setParent(RBTREE_NODE* node, RBTREE_NODE* parent);
	bool getColor(RBTREE_NODE* node);
	bool ifRedNode(RBTREE_NODE* node);
	bool ifBlackNode(RBTREE_NODE* node);
	void setNodeBlack(RBTREE_NODE* node);
	void setNodeColor(RBTREE_NODE* node, bool color);
	void setNodeRed(RBTREE_NODE* node);

	void leftRotate(RBTREE_NODE* & tree, RBTREE_NODE* node);
	void rightRotate(RBTREE_NODE* &tree, RBTREE_NODE* node);
	void insertFixup(RBTREE_NODE* &tree, RBTREE_NODE* node);
	void insertNodeInTree(RBTREE_NODE* &tree, RBTREE_NODE* node);
	void deleteFixup(RBTREE_NODE* &tree, RBTREE_NODE* node, RBTREE_NODE* parent);
	void deleteDataInTree(RBTREE_NODE*& tree, RBTREE_NODE* node);
	void deleteTree(RBTREE_NODE* tree);
	
	void displayTree(RBTREE_NODE* tree);
public:
	RBTree();
	~RBTree();
	bool insertData(RBTREE_DATA data);
	bool deleteData(RBTREE_DATA data);
	void display();
	//moved root_node to public
	RBTREE_NODE* root_node;
	//moved searchData to public
	RBTREE_NODE* searchData(RBTREE_NODE* tree, RBTREE_DATA data);


};


template<typename RBTREE_DATA>
RBTree<RBTREE_DATA>::RBTree()
{
	root_node = nullptr;
}

template<typename RBTREE_DATA>
RBTree<RBTREE_DATA>::~RBTree()
{
	if (root_node != nullptr) {
		deleteTree(root_node);
		root_node = nullptr;
	}
}

template<typename RBTREE_DATA>
typename RBTree<RBTREE_DATA>::RBTREE_NODE* RBTree<RBTREE_DATA>::getParent(RBTREE_NODE* node)
{
	return node->parent_node;
}

template<typename RBTREE_DATA>
void RBTree<RBTREE_DATA>::setParent(RBTREE_NODE* node, RBTREE_NODE* parent)
{
	node->parent_node = parent;
}

template<typename RBTREE_DATA>
bool RBTree<RBTREE_DATA>::getColor(RBTREE_NODE* node)
{
	return node->color;
}

template<typename RBTREE_DATA>
bool RBTree<RBTREE_DATA>::ifRedNode(RBTREE_NODE* node)
{
	return getColor(node) == RED_NODE;
}

template<typename RBTREE_DATA>
bool RBTree<RBTREE_DATA>::ifBlackNode(RBTREE_NODE* node)
{
	return getColor(node) == BLACK_NODE;
}

template<typename RBTREE_DATA>
void RBTree<RBTREE_DATA>::setNodeBlack(RBTREE_NODE* node)
{
	(node)->color = BLACK_NODE;
}

template<typename RBTREE_DATA>
void RBTree<RBTREE_DATA>::setNodeColor(RBTREE_NODE* node, bool color)
{
	(node)->color = color;
}

template<typename RBTREE_DATA>
void RBTree<RBTREE_DATA>::setNodeRed(RBTREE_NODE* node)
{
	(node)->color = RED_NODE;
}

template<typename RBTREE_DATA>
void RBTree<RBTREE_DATA>::deleteTree(RBTREE_NODE* tree)
{
	if (tree == nullptr) {
		return;
	}
	if (tree->left_node != nullptr) {
		deleteTree(tree->left_node);
	}
	if (tree->right_node != nullptr) {
		deleteTree(tree->right_node);
	}
	delete tree;
}

template<typename RBTREE_DATA>
void RBTree<RBTREE_DATA>::displayTree(RBTREE_NODE* tree)
{
	if (tree != nullptr)
	{
		displayTree(tree->left_node);
		cout << tree->data << " ";
		displayTree(tree->right_node);
	}
}

template<typename RBTREE_DATA>
bool RBTree<RBTREE_DATA>::insertData(RBTREE_DATA data)
{
	if (searchData(root_node, data) != nullptr) {
		return false;
	}
	RBTREE_NODE* new_node = new RBTREE_NODE;
	new_node->data = data;
	new_node->left_node = nullptr;
	new_node->right_node = nullptr;
	new_node->parent_node = nullptr;
	insertNodeInTree(root_node, new_node);
	return true;
}

template<typename RBTREE_DATA>
bool RBTree<RBTREE_DATA>::deleteData(RBTREE_DATA data)
{
	RBTREE_NODE* getNode= searchData(root_node, data);
	if (getNode == nullptr) {
		return false;
	}
	deleteDataInTree(root_node, getNode);
	return true;
}

template<typename RBTREE_DATA>
void RBTree<RBTREE_DATA>::display()
{
	if (root_node != nullptr) {
		displayTree(root_node);
		cout << endl;
	}
}


template<typename RBTREE_DATA>
void RBTree<RBTREE_DATA>::insertNodeInTree(RBTREE_NODE* &tree, RBTREE_NODE* node)
{
	RBTREE_NODE* y = nullptr;
	RBTREE_NODE* x = tree;
	while (x != nullptr)
	{
		y = x;
		if (node->data < x->data)
			x = x->left_node;
		else
			x = x->right_node;
	}
	setParent(node, y);

	if (y != nullptr)
	{
		if (node->data < y->data)
			y->left_node = node;
		else
			y->right_node = node;
	}
	else
	{
		tree = node;             
	}
	setNodeColor(node, RED_NODE);
	insertFixup(tree, node);
}

template<typename RBTREE_DATA>
typename RBTree<RBTREE_DATA>::RBTREE_NODE* RBTree<RBTREE_DATA>::searchData(RBTREE_NODE* tree, RBTREE_DATA data)
{
	if ((tree == nullptr) || (tree->data == data)) {
		return tree;
	}
	if (data < tree->data) {
		return searchData(tree->left_node, data);
	}
	else {
		return searchData(tree->right_node, data);
	}
}

template<typename RBTREE_DATA>
void RBTree<RBTREE_DATA>::insertFixup(RBTREE_NODE*& tree, RBTREE_NODE* node)
{
	RBTREE_NODE* parent;
	RBTREE_NODE* gparent;

	while ((parent = getParent(node)) && ifRedNode(parent))
	{
		gparent = getParent(parent);
		if (parent == gparent->left_node)
		{
			RBTREE_NODE* uncle = gparent->right_node;
			if (uncle && ifRedNode(uncle))
			{
				setNodeBlack(uncle);
				setNodeBlack(parent);
				setNodeRed(gparent);
				node = gparent;
				continue;
			}
			if (parent->right_node == node)
			{
				RBTREE_NODE* tmp;
				leftRotate(tree, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			setNodeBlack(parent);
			setNodeRed(gparent);
			rightRotate(tree, gparent);
		}
		else
		{
			RBTREE_NODE* uncle = gparent->left_node;
			if (uncle && ifRedNode(uncle))
			{
				setNodeBlack(uncle);
				setNodeBlack(parent);
				setNodeRed(gparent);
				node = gparent;
				continue;
			}
			if (parent->left_node == node)
			{
				RBTREE_NODE* tmp;
				rightRotate(tree, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			setNodeBlack(parent);
			setNodeRed(gparent);
			leftRotate(tree, gparent);
		}
	}
	setNodeBlack(tree);
}

template<typename RBTREE_DATA>
void RBTree<RBTREE_DATA>::leftRotate(RBTREE_NODE* & tree, RBTREE_NODE* node)
{
	RBTREE_NODE* y = node->right_node;
	node->right_node = y->left_node;
	if (y->left_node != nullptr) {
		y->left_node->parent_node = node;
	}
	y->parent_node = node->parent_node;
	if (node->parent_node == nullptr)
	{
		tree = y;       
	}
	else
	{
		if (node->parent_node->left_node == node) {
			node->parent_node->left_node = y;
		}
		else {
			node->parent_node->right_node = y;
		}
	}
	y->left_node = node;
	node->parent_node = y;
}

template<typename RBTREE_DATA>
void RBTree<RBTREE_DATA>::rightRotate(RBTREE_NODE* &tree, RBTREE_NODE* node)
{
	RBTREE_NODE* x = node->left_node;
	node->left_node = x->right_node;
	if (x->right_node != nullptr) {
		x->right_node->parent_node = node;
	}
	x->parent_node = node->parent_node;
	if (node->parent_node == nullptr)
	{
		tree = x;
	}
	else
	{
		if (node == node->parent_node->right_node) {
			node->parent_node->right_node = x;
		}
		else {
			node->parent_node->left_node = x;
		}
	}
	x->right_node = node;
	node->parent_node = x;
}

template<typename RBTREE_DATA>
void RBTree<RBTREE_DATA>::deleteDataInTree(RBTREE_NODE*& tree, RBTREE_NODE* node)
{
	RBTREE_NODE* child;
	RBTREE_NODE* parent;
	bool color;
	if ((node->left_node != nullptr) && (node->right_node != nullptr))
	{
		RBTREE_NODE* replace = node;
		replace = replace->right_node;
		while (replace->left_node != NULL) {
			replace = replace->left_node;
		}
		if (getParent(node))
		{
			if (getParent(node)->left_node == node) {
				getParent(node)->left_node = replace;
			}
			else {
				getParent(node)->right_node = replace;
			}
		}
		else {
			tree = replace;
		}
		child = replace->right_node;
		parent = getParent(replace);
		color = getColor(replace);
		if (parent == node)
		{
			parent = replace;
		}
		else
		{
			if (child) {
				setParent(child, parent);
			}
			parent->left_node = child;
			replace->right_node = node->right_node;
			setParent(node->right_node, replace);
		}
		replace->parent_node = node->parent_node;
		replace->color = node->color;
		replace->left_node = node->left_node;
		node->left_node->parent_node = replace;

		if (color == BLACK_NODE) {
			deleteFixup(tree, child, parent);
		}
		delete node;
		return;
	}
	if (node->left_node != nullptr) {
		child = node->left_node;
	}
	else {
		child = node->right_node;
	}
	parent = node->parent_node;
	color = node->color;
	if (child) {
		child->parent_node = parent;
	}
	if (parent)
	{
		if (parent->left_node == node) {
			parent->left_node = child;

		}
		else {
			parent->right_node = child;
		}
	}
	else {
		tree = child;
	}
	if (color == BLACK_NODE) {
		deleteFixup(tree, child, parent);
	}
	delete node;
}

template<typename RBTREE_DATA>
void RBTree<RBTREE_DATA>::deleteFixup(RBTREE_NODE* & tree, RBTREE_NODE* node, RBTREE_NODE* parent)
{
	RBTREE_NODE* other;
	while ((!node || ifBlackNode(node)) && node != tree)
	{
		if (parent->left_node == node)
		{
			other = parent->right_node;
			if (ifRedNode(other))
			{
				setNodeBlack(other);
				setNodeRed(parent);
				leftRotate(tree, parent);
				other = parent->right_node;
			}
			if ((!other->left_node || ifBlackNode(other->left_node)) &&
				(!other->right_node || ifBlackNode(other->right_node)))
			{
				setNodeRed(other);
				node = parent;
				parent = getParent(node);
			}
			else
			{
				if (!other->right_node || ifBlackNode(other->right_node))
				{
					setNodeBlack(other->left_node);
					setNodeRed(other);
					rightRotate(tree, other);
					other = parent->right_node;
				}
				setNodeColor(other, getColor(parent));
				setNodeBlack(parent);
				setNodeBlack(other->right_node);
				leftRotate(tree, parent);
				node = tree;
				break;
			}
		}
		else
		{
			other = parent->left_node;
			if (ifRedNode(other))
			{
				setNodeBlack(other);
				setNodeRed(parent);
				rightRotate(tree, parent);
				other = parent->left_node;
			}
			if ((!other->left_node || ifBlackNode(other->left_node)) &&
				(!other->right_node || ifBlackNode(other->right_node)))
			{
				setNodeRed(other);
				node = parent;
				parent = getParent(node);
			}
			else
			{
				if (!other->left_node || ifBlackNode(other->left_node))
				{
					setNodeBlack(other->right_node);
					setNodeRed(other);
					leftRotate(tree, other);
					other = parent->left_node;
				}
				setNodeColor(other, getColor(parent));
				setNodeBlack(parent);
				setNodeBlack(other->left_node);
				rightRotate(tree, parent);
				node = tree;
				break;
			}
		}
	}
	if (node) {
		setNodeBlack(node);
	}
}



#endif
