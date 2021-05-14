#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "RBTree.h"

using namespace std;

RBTREE_NODE* successor(RBTREE_NODE* x) {
	if(x.right_node != NULL) {
		x = x.right_node;
		while(x.left_node != NULL) x = x.left_node;
		return x;
	}
	RBTREE_NODE* y = x.parent_node;
	while(y != NULL && x == y.right_node) {
		x = y;
		y = y.parent_node;
	}
	return y;
}

void above(RBTree<int> &tree, vector<int> &ret, int data) {
	RBTREE_NODE* node = searchData(tree, data);
	RBTREE_NODE* max = tree.root_node;
	while(max.right_node != NULL) max = max.right_node;
	while(node != max) {
		node = successor(node);
		ret.push_back(node.data);
	}

}

void below(RBTree<int> &tree, vector<int> &ret, int data) {

}

int main(int argc, char *argv[])
{
	ifstream input;
	ofstream output;
	input.open(argv[1]);
	output.open(argv[2]);
	string instruction;
	int n;
	int data;
	RBTree<int> tree;
	input >> instruction;
	while(!input.eof()) {
		if(instruction.compare("Insert") == 0) {
			output << "Inserted to tree:";
			input >> n;
			for(int i = 0; i < n; i++) {
				input >> data;
				tree.insertData(data);
				output << " " << data;
			}
			output << "\n";
		}
		if(instruction.compare("Delete") == 0) {
			output << "Deleted from tree:";
			input >> n;
			for(int i = 0; i < n; i++) {
				input >> data;
				tree.deleteData(data);
				output << " " << data;
			}
			output << "\n";
		}
		if(instruction.compare("Above") == 0) {
			vector<int> ret;
			input >> data;
			output << "Above " << data << ":";
			above(tree, ret, data);
			for(int i = 0; i < ret.size(); i++) {
				output << " " << ret[i];
			}
			output << "\n";
		}
		if(instruction.compare("Below") == 0) {
			vector<int> ret;
			input >> data;
			output << "Below " << data << ":";
			below(tree, ret, data);
			for(int i = 0; i < ret.size(); i++) {
				output << " " << ret[i];
			}
			output << "\n";
		}
		input >> instruction;
	}

	//Test int
	RBTree<int>  test_tree; 
	test_tree.insertData(4);
	test_tree.insertData(1);
	test_tree.insertData(3);
	test_tree.insertData(2);
	test_tree.display();

	test_tree.deleteData(4);
	test_tree.display();
	test_tree.deleteData(3);
	test_tree.display();

	test_tree.deleteData(1);
	test_tree.display();
	test_tree.deleteData(2);
	test_tree.display();
	//Test string
	RBTree<string> test_string;
	test_string.insertData("4");
	test_string.insertData("1");
	test_string.insertData("3");
	test_string.insertData("2");
	test_string.display();

	test_string.deleteData("4");
	test_string.display();
	test_string.deleteData("3");
	test_string.display();

	test_string.deleteData("1");
	test_string.display();
	test_string.deleteData("2");
	test_string.display();

	return 0;
}
