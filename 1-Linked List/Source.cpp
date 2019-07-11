#include <vector> 
#include <iterator> 
#include <iostream>

using namespace std;

template <class T>
class List
{
	class Node
	{
	private:
		T value;
		Node* next;

	public:

		Node() { next = nullptr; value = 0; }
		Node(const Node& orig) : value(orig.value), next(orig.next) {}
		~Node() { delete& next; }

		Node* getprev(Node* h) 
		{
			Node* ptr = h;
			while (ptr->getnext() != this)
			{
				ptr = ptr->getnext();
			}
			return ptr;
		}
		Node* getnext() { if (this) return next; else return NULL; }
		T getvalue() { if (this) return value; else return NULL; }

		void setprev(Node* pr, Node* h)
		{
			Node* ptr = h;
			while (ptr->getnext() != this)
			{
				ptr = ptr->getnext();
			}
			ptr = pr;
		}
		void setnext(Node* nx) { next = nx; }
		void setvalue(T v) { value = v; }
	};

	int len;
	Node* head, * tail, * ptr;

public:
	class iter : public iterator<bidirectional_iterator_tag, T>
	{
	public:

		Node* ptr;

		iter() : ptr(0) {}
		iter(Node* p) : ptr(p) {}

		iter& operator++ (int) { ptr = ptr->getnext();	return *this; }
		iter& operator++ () { ptr = ptr->getnext();	return *this; }
		iter& operator+ (int a) { for (int i = 0; i < a; i++) { ptr = ptr->getnext(); }	return *this; }
		Node& operator* () { return *ptr; }
		int& operator-> () { return ptr->getvalue(); }
		bool operator== (iter& right) { return ptr == right.ptr; }
		bool operator!= (iter& right) { return ptr != right.ptr; }

		T operator()() const { return ptr->getvalue(); }
	};

	List() : head(nullptr), tail(nullptr), ptr(nullptr), len(0) {}
	List(const List& orig) : len(orig.len), head(orig.head), tail(orig.tail), ptr(orig.tail) {}
	~List() { }

	iter begin() { return iter(head); }
	iter end() { return iter(tail); }

	int getLen() { return len; }
	Node* gethead() { return head; }
	Node* gettail() { return tail; }

	void addHead(int val);
	void addTail(int val);
	void insert_pos(T val, int pos);
	void insert_node_pos(Node* n, int pos);
	void insert(T val);
	void del(Node* n);

	void sort(iter first, iter last);

	void print();
	template <class T> friend ostream& operator<< (ostream& out, List<T>& L)
	{
		if (L.len != 0)
		{
			iter its = L.begin();
			iter ite = L.end();

			while (its != ite)
			{
				out << its() << ", ";
				its++;
			}
			out << ite() << endl;
		}
		return out;
	}
	template <class T> friend istream& operator>> (istream& in, List<T>& L);
};

template<class T> void List<T>::addHead(int val)
{
	Node* temp = new Node;
	//temp->setprev(0, gethead());
	temp->setvalue(val);
	temp->setnext(head);
	if (head != 0)
		head->setprev(temp, gethead());
	if (len == 0)
		head = tail = temp;
	else
		head = temp;
	len++;
}

template<class T> void List<T>::addTail(int val)
{
	Node* temp = new Node;
	temp->setnext(0);
	temp->setvalue(val);
	//temp->setprev(tail, gethead());
	if (tail != 0)
		tail->setnext(temp);
	if (len == 0)
		head = tail = temp;
	else
		tail = temp;
	len++;
}

template<class T> void List<T>::insert_pos(T val, int pos)
{
	if (pos == len + 1)
	{
		addTail(val);
		return;
	}
	else if (pos == 1)
	{
		addHead(val);
		return;
	}

	int i = 1;
	Node* Ins = head;
	while (i < pos)
	{
		Ins = Ins->getnext();
		i++;
	}
	Node* PrevIns = Ins->getprev(gethead());
	Node* temp = new Node;

	if (PrevIns != 0 && len != 1)
		PrevIns->setnext(temp);

	temp->setnext(Ins);
	temp->setprev(PrevIns, gethead());
	temp->setvalue(val);
	Ins->setprev(temp, gethead());
	len++;
}

template<class T> void List<T>::insert_node_pos(Node * n, int pos)
{
	insert_pos(n->getvalue(), pos);
}


template<class T> void List<T>::del(Node * n)
{
	if (len == 1) { len = 0; return; }

	Node* Prev = n->getprev(gethead());
	Node* Next = n->getnext(gethead());

	if (Prev && Next)
	{
		n.next->setprev(Prev, gethead());
		n.prev->setnext(Next);
	}
	else
	{
		if (Prev) n.prev->setnext(nullptr);
	}

	len--;
}

template<class T> void List<T>::insert(T val)
{
	if (val >= tail->getvalue())
	{
		addTail(val);
		return;
	}
	else if (val <= head->getvalue())
	{
		addHead(val);
		return;
	}

	int i = 1;
	Node* Ins = head;
	while (val < Ins->getvalue())
	{
		Ins = Ins->getnext();
		i++;
	}
	Node* PrevIns = Ins->getprev(gethead());
	Node* temp = new Node;

	if (PrevIns != 0 && len != 1)
		PrevIns->setnext(temp);

	temp->setnext(Ins);
	temp->setprev(PrevIns, gethead());
	temp->setvalue(val);
	Ins->setprev(temp, gethead());
	len++;
}

template<class T> void List<T>::sort(iter first, iter last)
{
	iter i = begin();
	iter e = end();
	while (i != e)
	{
		T val_i = i();
		T val_e = end()();

		if (i() > end()())
		{
			i.ptr->setvalue(val_e);
			end().ptr->setvalue(val_i);
		}
		i = iter(i.ptr->getnext());
	}
}

template<class T> void List<T>::print()
{
	if (len != 0)
	{
		iter its = begin();
		iter ite = end();

		while (its != ite)
		{
			cout << its() << ", ";
			its++;
		}
		cout << ite() << endl;
	}
}

template <class T> istream& operator>> (istream & in, List<T> & L)
{
	List<T> L1;
	cout << "\nHow many elements: ";
	int N;
	in >> N;
	for (int i = 1; i <= N; i++)
	{
		T el;
		cout << "\telement #" << i << ": ";
		cin >> el;
		L1.insert_pos(el, i);
	}
	L = L1;
	return in;
}

int main()
{
	cout << endl << "----------- 2-linked list -----------" << endl;

	List<int> L;
	L.addHead(20);
	L.addTail(40);
	L.insert_pos(30, 3);
	L.insert_pos(10, 4);

	cout << endl << "List (" << L.getLen() << " elements):\n";
	L.print();
	cout << endl;

	L.sort(L.begin(), L.end());
	cout << endl << "Sorted:\n";
	L.print();
	cout << endl;

	List<int>L2;
	cin >> L2;
	cout << endl << "List 2 (" << L2.getLen() << " elements):\n" << L2;

	return 0;
}