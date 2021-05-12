#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

enum Color {RED, BLACK};

struct Node
{
    int price;
    bool color;
    Node *left, *right, *parent;

    // Constructor
    Node(int data)
    {
       this->price = data;
       left = right = parent = NULL;
       this->color = RED;
    }
};




// A recursive function to do inorder traversal
void inorderHelper(Node *root)
{

}

/* A utility function to insert
    a new node with given key
   in BST */
Node* BSTInsert(Node* root, Node *pt)
{

}

// Utility function to do level order traversal
void levelOrderHelper(Node *root)
{

}



int main(int argc, char *argv[])
{
	ifstream input;
	ofstream output;
	input.open(argv[1]);
	output.open(argv[2]);
	float val;
	input >> val;
	while(!input.eof()) {
		//insert node with val as its cost
		//call the algorithm
		input >> val;
	}
	input.close();
	output.close();
	return 0;
}
