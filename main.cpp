#include <iostream>
#include <fstream>
#include <string>

#include "RBTree.h"

using namespace std;


int main(int argc, char *argv[])
{
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
