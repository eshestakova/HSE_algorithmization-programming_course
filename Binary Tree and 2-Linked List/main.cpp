#include <iostream> 
#include <vector> 
#include <iterator> 
#include "2List.cpp"  
#include "BinTree.cpp"

using namespace std;

int main()
{
	cout << endl << "----------- 2-Linked List -----------" << endl;
	List<int> L;
	L.insert(20, 1);
	L.insert(40, 2);
	L.insert(10, 1);

	cout << endl << "List (" << L.getLen() << " elements):\n";
	L.print();

	cout << endl << "*inserting element " << 30 << " into position " << 3 << "*" << endl;
	L.insert(30, 3);

	cout << endl << "List (" << L.getLen() << " elements):\n";
	L.print();
	cout << endl;

	cout << endl << "----------- Binary tree -------------" << endl << endl;
	struct Node<int> *root;
	root = NULL;

	cout << "*adding new elements: 61, 27, 78*" << endl;
	root = addnode(61, root);
	root = addnode(27, root);
	root = addnode(78, root);
	root->print();

	cout << endl << endl << "*adding new elements: 11, 49, 51, 199*" << endl;
	root = addnode(11, root);
	root = addnode(49, root);
	root = addnode(51, root);
	root = addnode(199, root);
	root->print();


	return 0;
}