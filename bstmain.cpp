#include "bst.h"

int main()
{
	BST tree;
	cout << "inserting 7" << endl;
	tree.insert("7");
	cout << "inserting 4" << endl;
	tree.insert("4");
	// cout << "inserting 12" << endl;
	// tree.insert("12");
	cout << "inserting 1" << endl;
	tree.insert("1");
	cout << "inserting 6" << endl;
	tree.insert("6");
	cout << "inserting 8" << endl;
	tree.insert("8");
	// cout << "inserting 14" << endl;
	// tree.insert("14");
	cout << "inserting 3" << endl;
	tree.insert("3");
	cout << "inserting 2" << endl;
	tree.insert("2");
	cout << "inserting 5" << endl;
	tree.insert("5");
	tree.remove("2");
	int size = tree.size();
	int height = tree.height();
	if (tree.contains("5"))
	{
		cout << "Found 5 in tree" << endl;
	}
	cout << "The size is: " << size << endl;
	cout << "The height is: " << height << endl;
	cout << "Pre order: ";
	tree.print_preorder();
	cout << "In order: ";
	tree.print_inorder();
	cout << "Post order: ";
	tree.print_postorder();
	return 0;
}
