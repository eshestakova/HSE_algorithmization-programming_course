#include <vector> 
#include <iterator> 
#include <iostream> 

using namespace std;

template <class T>
class DirGraph
{
public:

	class iter : public iterator<bidirectional_iterator_tag, T>
	{
	private:
		int num;
	public:
		iter() { num = 0; }
		iter(iter  &it) { num = it.num; }
		iter(iter &&it) { num = it.num; }
		iter(int num) { this->num = num; }
		~iter() {}

		bool operator!=(iter &it) const { return num != it.num; }
		bool operator==(iter &it) const { return num == it.num; }

		iter& operator=(iter  &it) { num = it.num; return *this; }
		iter& operator++(int) { num++; return *this; }
		iter& operator--(int) { num--; return *this; }
		iter& operator+(int n) { num += n; return *this; }
		iter& operator-(int n) { num -= n; return *this; }

		int operator()() const { return num; }
	};
	typedef iter iterator; 

private:
	vector<T> values;
	vector<vector<int>> connections;
	int length;

public:
	int size() const { return length; }

	DirGraph(int l, vector<vector<int>> c, vector<T> v)
	{
		length = l;
		values = v;
		connections = c;
	}
	DirGraph(DirGraph &g)
	{
		length = g.length;
		values = g.values;
		connections = g.connections;
	}
	~DirGraph() {}

	void addElem(vector<int> c, T v)
	{
		for (int i = 0; i < length; i++)
			connections.at(i).push_back(c.at(i)*(-1));
		
		connections.push_back(c);
		values.push_back(v);
		length++;

	}
	void delElem(iterator it)
	{
		int num = it();
		connections.erase(connections.begin() + num);
		values.erase(values.begin() + num);
		for (int i = 0; i < length - 1; i++)
			connections.at(i).erase(connections.at(i).begin() + num);
		length--;
	}

	void print(iterator &it) const
	{
		cout << values.at(it()) << " (No " << it() + 1 << ")" << endl;
		cout << "\tIncoming: ";
		for (int i = 0; i < length; i++)
		{
			if (connections.at(it()).at(i) == -1)
				cout << i + 1 << " ";
		}
		cout << endl;

		cout << "\tOutgoing: ";
		for (int i = 0; i < length; i++)
		{
			if (connections.at(it()).at(i) == 1)
				cout << i + 1 << " ";
		}
		cout << endl << endl;
	}

	void print(iterator start, iterator &end) const
	{
		while (start() != end())
		{
			print(start);
			start++;
		}
		print(end);
		cout << endl;
	}

	void printEven(iterator start, iterator &end) const
	{
		while (start() <= end()) {
			if (start() % 2 != 0)
				print(start);
			start++;
		}
		cout << endl;
	}

	void printOdd(iterator start, iterator &end) const
	{
		while (start() <= end()) {
			if (start() % 2 == 0)
				print(start);
			start++;
		}
		cout << endl;
	}

	iterator begin() const { return iterator(0); }
	iterator end() const { return iterator(length - 1); }
};