#include <iostream> 
#include <vector> 
#include <iterator> 
#include "bin_list.cpp"  
#include "queue.cpp"

using namespace std;

int main()
{
	List<int> List;

	List.insert(165, 1);
	List.insert(778, 2);
	List.insert(1, 3);
	List.insert(89, 2);

	cout << endl << "BinList - " << List.getLength() << " Elements" << endl;
	List.print();
	cout << endl << "New Elem " << 177 << ", Pos Num " << 3 << endl;
	List.insert(177, 3);
	cout << endl << "BinList - " << List.getLength() << " Elements" << endl;
	List.print();
	cout << endl;

	vector<int> Row = { 11, 12, 13, 14, 15 };
	queue<int> Queue(Row);
	queue<int>::iterator Iter;
	Iter = Queue.begin();
	Queue.add_elem(10);

	return 0;
}