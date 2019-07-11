#include <iostream> 
#include <vector> 
#include <iterator> 
#include "DirGraph.cpp" 

using namespace std;

int main()
{
	cout << endl << "----------- Directed graph -----------" << endl << endl;

	vector<vector<int>> connections = { {0, 1, -1, 1}, {-1, 0, 0, -1}, {1, 1, 0, 0}, {-1, 0, 0, 0} };
	vector<int> values = { 5, 4, 3, 2 };

	DirGraph<int> G(4, connections, values);
	DirGraph<int>::iterator it1 = G.begin();
	DirGraph<int>::iterator it2 = G.end();

	cout << "----> All graph (" << G.size() << " elements):" << endl << endl;
	G.print(it1, it2);
	cout << "----> Even elements:" << endl << endl;
	G.printEven(it1, it2);
	cout << "----> Odd elements:" << endl << endl;
	G.printOdd(it1, it2);

	return 0;
}